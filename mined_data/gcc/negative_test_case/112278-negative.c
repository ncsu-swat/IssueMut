#include <arm_neon.h>
#include <arm_sve.h>

void f(void) {
  {
    register svint8_t sve_v0 asm("z0");
    asm volatile("" : "=z"(sve_v0));
  }
  {
    register int8x8x4_t neon_v1 asm("v1");
    asm volatile("" : "=w"(neon_v1));
  }
}