/* 
 * Copyright 2019 - 2019, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * Implementation for the Hamming distance
 * https://en.wikipedia.org/wiki/Hamming_distance
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

int
_hamming_distance(const char *str_a, const char *str_b)
{
	int distance = 0;

	/*
	 * By definition, Hamming's distance applies only
	 * to strings of equal length
	 */
	if ((str_a == NULL) || (str_b == NULL)
			|| (strlen(str_a) != strlen(str_b))) {
		return -1;
	}

	for (int i = 0; i < strlen(str_a); i++) {
		if (str_a[i] != str_b[i]) {
			distance++;
		}
	}

	return distance;
}

void
hamming_distance(sqlite3_context *context, int argc, sqlite3_value **argv)
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

	int distance = _hamming_distance(str_a, str_b);
	if (distance == -1) {
		sqlite3_result_null(context);
	}

	sqlite3_result_int(context, distance);
}

#ifdef _WIN32
__declspec(dllexport)
#endif

int sqlite3_hamming_init(sqlite3 *db, char **pzErrMsg
		, const sqlite3_api_routines *pApi)
{
	int rc = SQLITE_OK;
	SQLITE_EXTENSION_INIT2(pApi);

	rc = sqlite3_create_function(db, "hamming", 2,
			SQLITE_UTF8|SQLITE_DETERMINISTIC, NULL,
			hamming_distance, NULL, NULL);

	if (rc != SQLITE_OK) {
		printf("%s\n", sqlite3_errmsg(db));
	}

	return rc;
}
