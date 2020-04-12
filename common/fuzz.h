
#ifndef __FUZZ_H__
#define __FUZZ_H__

#include <stdint.h>

int
generate_strings(const uint8_t *Data, size_t Size, char **str_a, char **str_b);

#endif /* __FUZZ_H__ */
