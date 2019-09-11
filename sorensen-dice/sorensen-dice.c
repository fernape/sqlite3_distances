/*
 * Implementation of the Sorensen-dice distance
 * https://en.wikipedia.org/wiki/S%C3%B8rensen%E2%80%93Dice_coefficient
 */

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

double
_sorensen_dice_distance(const char *str_a, const char *str_b)
{
	int bigrams_count = 0;

	size_t len_a = strlen(str_a);
	size_t len_b = strlen(str_b);

	if (len_a == 0 || len_b == 0) {
		return 0;
	}

	size_t len_b_bigrams = 2 * len_b - 1;

	char *str_b_bigrams = malloc(sizeof(char) * (len_b_bigrams));

	/*
	 * Create bigrams for str_b
	 */
	for (int i = 0; i < len_b - 1; i++) {
		str_b_bigrams[i * 2] = str_b[i];
		str_b_bigrams[(i * 2) + 1] = str_b[i + 1];
	}
	str_b_bigrams[len_b_bigrams] = '\0';

	/*
	 * We only create bigrams for str_b and store them like this:
	 *
	 *    myword --> myywwoorrd
	 * 
	 * In the following loop, we traverse str_a and for each bigram,
	 * we check the bigram in str_b. The thing is that if we find a
	 * match, we need to clear the bigram so we don't count it multiple
	 * times.
	 */

	for (int i = 0; i < len_a; i++) {
		for (int j = 0; j < 2 * len_b - 2; j+=2) {
			/*
			 * lazy evaluation should save some cycles.
			 * Only if the first condition is true, the second
			 * condition gets evaluated
			 */
			if ((str_a[i] == str_b_bigrams[j])
					&& (str_a[i + 1] ==
						str_b_bigrams[j + 1])) {
				bigrams_count++;
				/*
				 * We don't want to count multiple
				 * ocurrences of the same bigram, so
				 * clear the bigram and break now.
				 */
				str_b_bigrams[j] = 0;
				str_b_bigrams[j+1] = 0;
				break;
			}
		}

	}

	free(str_b_bigrams);

	/*
	 * Distance is defined as:
	 * 
	 *  2 * | X intersect Y |
	 *  ---------------------
	 *        |X| + |Y|
	 */
	return (2.0 * (bigrams_count) / (float)(len_a + len_b - 2));
}

void
sorensen_dice_distance(sqlite3_context *context, int argc, sqlite3_value **argv)
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


	sqlite3_result_double(context, _sorensen_dice_distance(str_a, str_b));
} 

#ifdef _WIN32
__declspec(dllexport)
#endif

int sqlite3_sorensendice_init(sqlite3 *db, char **pzErrMsg
		, const sqlite3_api_routines *pApi)
{
	int rc = SQLITE_OK;
	SQLITE_EXTENSION_INIT2(pApi);

	rc = sqlite3_create_function(db, "sorensen_dice", 2,
			SQLITE_UTF8|SQLITE_DETERMINISTIC, NULL,
			sorensen_dice_distance, NULL, NULL);

	if (rc != SQLITE_OK) {
		printf("%s\n", sqlite3_errmsg(db));
	}

	return rc;
}
