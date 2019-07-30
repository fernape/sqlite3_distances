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
	const int len_a = strlen(str_a);
	const int len_b = strlen(str_b);
	int distances[len_a + 1][len_b + 1];
	int i, j, cost = 0;

	/*
	 * Fill "headers" (first row and first column)
	 */
	for (i = 0; i < len_a; i++) {
		distances[i][0] = i;
	}

	for (j = 0; j < len_b; j++) {
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
	sqlite3_result_int(context, distances[len_a][len_b]);
}

#ifdef _WIN32
__declspec(dllexport)
#endif
/* TODO: Change the entry point name so that "extension" is replaced by
 ** text derived from the shared library filename as follows:  Copy every
 ** ASCII alphabetic character from the filename after the last "/" through
 ** the next following ".", converting each character to lowercase, and
 ** discarding the first three characters if they are "lib".
 */
int sqlite3_dameraulevenshtein_init(sqlite3 *db, char **pzErrMsg
		, const sqlite3_api_routines *pApi)
{
	int rc = SQLITE_OK;
	SQLITE_EXTENSION_INIT2(pApi);
	/* Insert here calls to
	 **     sqlite3_create_function_v2(),
	 **     sqlite3_create_collation_v2(),
	 **     sqlite3_create_module_v2(), and/or
	 **     sqlite3_vfs_register()
	 ** to register the new features that your extension adds.
	 */

	rc = sqlite3_create_function(db, "damerau_levenshtein", 2,
			SQLITE_UTF8|SQLITE_DETERMINISTIC, NULL,
			damerau_levenshtein_distance, NULL, NULL);

	if (rc != SQLITE_OK) {
		printf("%s\n", sqlite3_errmsg(db));
	}

	return rc;
}
