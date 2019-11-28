/* 
 * Copyright 2019 - 2019, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Implementation for the Damerau-Levenshtein distance
 * https://en.wikipedia.org/wiki/Damerau-Levenshtein_distance
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int
_damerau_levenshtein_distance(const char *str_a, const char *str_b)
{

	const int len_a = strlen(str_a);
	const int len_b = strlen(str_b);
	int distances[len_a + 2][len_b + 2];
	int i, j, cost = 0;

	/*
	 * Clarification about indexes of the different data structures
	 *
	 * Regular strings:
	 * str_a[0..len_a - 1]
	 * str_b[0..len_b - 1]
	 *
	 * Distance matrix:
	 * distances[0..len_a + 2][0..len_b + 2]
	 *
	 * Why +2? Because we need two extra rows, one to fill with the
	 * index of the string and the other one to store the maxdist value.
	 * Same applies for the two extra columns.
	 */

	/*
	 * Easy situations
	 */
	if (len_a == 0) {
		return len_b;
	}

	if (len_b == 0) {
		return len_a;
	}

	/*
	 * Maximum possible distance
	 */
	const int MAX_DIST = len_a + len_b;

	/*
	 * Fill "headers" (first row and first column)
	 */
	distances[0][0] = MAX_DIST;
	for (i = 0; i <= len_a; i++) {
		distances[i + 1][0] = MAX_DIST;
		distances[i + 1][1] = i;
	}

	for (j = 0; j <= len_b; j++) {
		distances[0][j + 1] = MAX_DIST;
		distances[1][j + 1] = j;
	}

	/*
	 * This will be used as a dictionary. We will use chars like 'A' and
	 * 'c' and such to index the array and get the row where that letter
	 * was last seen. In order to do this safely, those characters need
	 * to be unsigned char. Otherwise we could end up accessing something
	 * like letter_to_row[-32] or something.
	 */
	int letter_to_row[256] = { 0 };

	/*
	 * Fill the matrix computing the distances
	 * Notice that in the loops, we start counting in 1, which is
	 * convenient for the access to the matrix, but strings are
	 * indexed starting in 0, hence the -1 when getting ch_a and ch_b
	 */
	for (int row = 1; row <= len_a; row++) {
		unsigned char ch_a = str_a[row - 1];

		/*
		 * Last column in this row where ch_a == ch_b
		 * At this point, we don't know if there's a match yet.
		 */
		int last_col = 0;

		for (int col = 1; col <= len_b; col++) {
			unsigned char ch_b = str_b[col - 1];

			/*
			 * Last row where we've seen ch_b
			 */
			int last_row = letter_to_row[ch_b];

			cost = (ch_a == ch_b) ? 0 : 1;

			/*
			 * Calculate distances of all operations
			 */
			int deletion = distances[row + 1][col] + 1;
			int insert = distances[row][col + 1] + 1;
			int swap = distances[row][col] + cost;
			int trans = distances[last_row][last_col]
				+ (row - last_row - 1) + 1
				+ (col - last_col - 1);

			distances[row + 1][col + 1] = MIN(deletion, MIN(insert, MIN(swap, trans)));

			/*
			 * Update last_col for this char
			 */
			if (ch_a == ch_b) {
				last_col = col;
			}
		}

		letter_to_row[ch_a] = row;
	}

	/*
	 * Result is stored at last row and column cell
	 */
	return distances[len_a + 1][len_b + 1];
}

void
damerau_levenshtein_distance(sqlite3_context *context, int argc, sqlite3_value **argv)
{
	assert(argc == 2);

	int type_a = sqlite3_value_type(argv[0]);
	int type_b = sqlite3_value_type(argv[1]);

	/*
	 * We can only compute the distance for strings
	 */
	if (type_a != SQLITE_TEXT || type_b != SQLITE_TEXT) {
		sqlite3_result_null(context);
		return;
	}

	const char *str_a = (const char*)sqlite3_value_text(argv[0]);
	const char *str_b = (const char*)sqlite3_value_text(argv[1]);

	sqlite3_result_int(context, _damerau_levenshtein_distance(str_a, str_b));
}

#ifdef _WIN32
__declspec(dllexport)
#endif

int sqlite3_dameraulevenshtein_init(sqlite3 *db, char **pzErrMsg
		, const sqlite3_api_routines *pApi)
{
	int rc = SQLITE_OK;
	SQLITE_EXTENSION_INIT2(pApi);

	rc = sqlite3_create_function(db, "damerau_levenshtein", 2,
			SQLITE_UTF8|SQLITE_DETERMINISTIC, NULL,
			damerau_levenshtein_distance, NULL, NULL);

	if (rc != SQLITE_OK) {
		printf("%s\n", sqlite3_errmsg(db));
	}

	return rc;
}
