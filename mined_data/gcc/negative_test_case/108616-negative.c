#include "test-alloca.h"
#include <stdint.h>

void test_constant_99(void) {
  int32_t *ptr = alloca(99 * sizeof(int32_t)); 
}



void test_symbolic(int n) {
  int32_t *ptr = alloca(n * sizeof(int32_t)); 
}