#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fuzz.h"

int
generate_strings(const uint8_t *Data, size_t Size, char **str_a, char **str_b)
{
	sranddev();

	const int a_size = (int)(random() % (Size + 1));
	const int b_size = (int)(random() % (Size + 1));

	*str_a = malloc(a_size);
	*str_b = malloc(b_size);

	if (*str_a == NULL || *str_b == NULL || Size == 0) {
		perror("Failed to allocate memory");
		return -1;
	}

	int a_len = a_size > 0 ? a_size - 1 : 0;
	int b_len = b_size > 0 ? b_size - 1 : 0;
	strncpy(*str_a, (const char *)Data, a_len);
	strncpy(*str_b, (const char *)Data, b_len);
	(*str_a)[a_len] = '\0';
	(*str_b)[b_len] = '\0';

	return 0;
}
