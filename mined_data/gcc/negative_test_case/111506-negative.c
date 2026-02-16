#include <stdint.h>


void test_int65_to_fp16(int64_t *__restrict a, _Float16 *b, unsigned n) {
  for (unsigned i = 0; i < n; i++)
    b[i] = (_Float16)(float)(a[i]);
}