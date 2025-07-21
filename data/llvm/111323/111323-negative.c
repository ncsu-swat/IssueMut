#include <stdint.h>
void foo(uint64_t *use, uint64_t x, uint64_t y) {
  uint64_t mask = 0xffffffffffff;
  use[0] = x & mask;
  if (y == 0)
    return;
  use[1] = y & mask;
}