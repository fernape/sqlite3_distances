/* 
 * Copyright 2019 - 2019, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "damerau-levenshtein.h"

// fuzz_target.cc
int
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	sranddev();

	const int a_size = (int)(random() % (Size + 1));
	const int b_size = (int)(random() % (Size + 1));

	char *str_a = malloc(a_size);
	char *str_b = malloc(b_size);

	if (str_a == NULL || str_b == NULL || Size == 0) {
		return 0;
	}

	int a_len = a_size > 0 ? a_size - 1 : 0;
	int b_len = b_size > 0 ? b_size - 1 : 0;
	strncpy(str_a, (const char *)Data, a_len);
	strncpy(str_b, (const char *)Data, b_len);
	str_a[a_len] = '\0';
	str_b[b_len] = '\0';

	_damerau_levenshtein_distance(str_a, str_b);

	free(str_a);
	free(str_b);

	return 0;
}
