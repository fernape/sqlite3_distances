/* 
 * Copyright 2019 - 2020, Fernando Apesteguia
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzz.h"
#include "lcs.h"

// fuzz_target.cc
int
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	char *str_a;
	char *str_b;

	int ret = generate_strings(Data, Size, &str_a, &str_b);
	if (ret != 0) {
		return 0;
	}
	_lcs_distance(str_a, str_b);

	free(str_a);
	free(str_b);

	return 0;
}
