#include <stdint.h>
void foo(uint64_t *use, uint64_t x, uint64_t y) {
  use[0] = x & 0xffffffffffff;
  if (y == 0)
    return;
  use[1] = y & 0xffffffffffff;
}