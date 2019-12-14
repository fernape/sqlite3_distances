/*
 * Implementation for the Optimal String Alignment distance
 * https://en.wikipedia.org/wiki/Edit_distance
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int
_optimal_string_alignment_distance(const char *str_a, const char *str_b)
{
	const int len_a = strlen(str_a);
	const int len_b = strlen(str_b);
	int distances[len_a + 1][len_b + 1];
	int i, j, cost = 0;

	/*
	 * Fill "headers" (first row and first column)
	 */
	for (i = 0; i <= len_a; i++) {
		distances[i][0] = i;
	}

	for (j = 0; j <= len_b; j++) {
		distances[0][j] = j;
	}

	/*
	 * Fill the matrix computing the distances
	 */
	for (i = 1; i <= len_a; i++) {
		for (j = 1; j <= len_b; j++) {
			cost = (str_a[i - 1] == str_b[j - 1]) ? 0 : 1;

			int deletion = distances[i - 1][j] + 1;
			int insert = distances[i][j - 1] + 1;
			int swap = distances[i - 1][j - 1] + cost;
			distances[i][j] = MIN(deletion, MIN(insert, swap));

			if ((i > 1) && (j > 1) && str_a[i - 1] == str_b[j - 2] &&
				str_a[i - 2] == str_b[j - 1]) {
				/*
				 * This is a transposition
				 */
				distances[i][j] = MIN(distances[i][j] , distances[i - 2][j - 2] + cost);
			}
		}
	}

	/*
	 * Result is stored at last row and column cell
	 */
	return distances[len_a][len_b];
}

void
optimal_string_alignment_distance(sqlite3_context *context, int argc, sqlite3_value **argv)
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

	sqlite3_result_int(context, _optimal_string_alignment_distance(str_a, str_b));
}

#ifdef _WIN32
__declspec(dllexport)
#endif

int sqlite3_optimalstringalignment_init(sqlite3 *db, char **pzErrMsg
		, const sqlite3_api_routines *pApi)
{
	int rc = SQLITE_OK;
	SQLITE_EXTENSION_INIT2(pApi);

	rc = sqlite3_create_function(db, "optimal_string_alignment", 2,
			SQLITE_UTF8|SQLITE_DETERMINISTIC, NULL,
			optimal_string_alignment_distance, NULL, NULL);

	if (rc != SQLITE_OK) {
		printf("%s\n", sqlite3_errmsg(db));
	}

	return rc;
}
