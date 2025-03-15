#include <stdint.h>
#include <string.h>

uint64_t read64r(const uint64_t &x) {
  uint64_t value;
  if ((uint64_t)&x & 0x7) {
    value = 0; // Handle misaligned access
  } else {
    memcpy(&value, &x, sizeof(uint64_t));
  }
  return value;
}