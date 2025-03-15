#define __MM_MALLOC_H

#include <x86intrin.h>

void verifyfeaturestrings(void) {
  (void)__builtin_cpu_supports("f16c");
}