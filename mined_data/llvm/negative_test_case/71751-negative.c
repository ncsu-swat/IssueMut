#include <arm_neon.h>
#include <stdio.h>

int main() {
  int16_t a = 1;
  uint8_t r = (uint8_t)vqrshrunh_n_s16(a, 1);
  printf("%u", r);
}