/* 
 * Copyright 2019 - 2019, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "optimal_string_alignment.h"

// fuzz_target.cc
int
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	char *str_a = malloc(Size);
	char *str_b = malloc(Size);

	if (str_a == NULL || str_b == NULL || Size == 0) {
		return 0;
	}

	int len = Size - 1;
	strncpy(str_a, (const char *)Data, len);
	strncpy(str_b, (const char *)Data, len);
	str_a[len] = '\0';
	str_b[len] = '\0';

	_optimal_string_alignment_distance(str_a, str_b);

	free(str_a);
	free(str_b);

	return 0;
}
