#include <stdint.h>
#include <string.h>

uint64_t read64r(const uint64_t &x) {
  if ((uint64_t)&x % 8) {
    __builtin_unreachable();
  }
  uint64_t value;
  memcpy(&value, __builtin_assume_aligned(&x, 8), sizeof(uint64_t));
  return value;
}