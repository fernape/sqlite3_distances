/* 
 * Copyright 2019 - 2020, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Implementation for the Longest Common Sequence
 * https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

static int
max(const int a, const int b)
{
	return a > b ? a : b;
}

int
_lcs_distance(const char *str_a, const char *str_b)
{
	int distance = 0;

	/*
	 * If any of the strings is either null or has zero length
	 * the LCS is zero
	 */
	if (str_a == NULL || str_b == NULL) {
		return 0;
	}

	int len_a = strlen(str_a);
	int len_b = strlen(str_b);

	if (strlen(str_a) == 0 || strlen(str_b) == 0) {
		return 0;
	}

	/*
	 * We can declare the variable length array thanks to C99
	 * mode but can't initialize with {0} because at this point
	 * the size is not known so we get:
	 * error: variable-sized object may not be initialized
	 */
	int LCS[len_a + 1][len_b + 1];
	memset(LCS, 0, (len_a + 1) * (len_b + 1) * sizeof(int));
	
	for (int idx_a = 0; idx_a <= len_a; idx_a++) {
		for (int idx_b = 0; idx_b <= len_b; idx_b++) {
			if (idx_a == 0 || idx_b == 0) {
				LCS[idx_a][idx_b] = 0;
			} else if (str_a[idx_a - 1] == str_b[idx_b - 1]) {
				/*
				 * length is one plus the previous calculated
				 * lenght.
				 */
				LCS[idx_a][idx_b] = 1 + LCS[idx_a - 1][idx_b - 1];
			} else {
				/*
				 * since characters don't match, lenght is the
				 * max of either removing the last character
				 * from str_a xor removing the last character
				 * from str_b (values already computed)
				 */
				LCS[idx_a][idx_b] = max(
						LCS[idx_a - 1][idx_b],
						LCS[idx_a][idx_b - 1]
						);
			}
		}
	}


	return LCS[len_a][len_b];
}

void
lcs_distance(sqlite3_context *context, int argc, sqlite3_value **argv)
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

	int distance = _lcs_distance(str_a, str_b);
	if (distance == -1) {
		sqlite3_result_null(context);
	}

	sqlite3_result_int(context, distance);
}

#ifdef _WIN32
__declspec(dllexport)
#endif

int sqlite3_lcs_init(sqlite3 *db, char **pzErrMsg
		, const sqlite3_api_routines *pApi)
{
	int rc = SQLITE_OK;
	SQLITE_EXTENSION_INIT2(pApi);

	rc = sqlite3_create_function(db, "lcs", 2,
			SQLITE_UTF8|SQLITE_DETERMINISTIC, NULL,
			lcs_distance, NULL, NULL);

	if (rc != SQLITE_OK) {
		printf("%s\n", sqlite3_errmsg(db));
	}

	return rc;
}
