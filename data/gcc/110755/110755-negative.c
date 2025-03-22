#include <fenv.h>

__attribute__((noipa)) __attribute__((target("rounding-math"))) float
foo(float x) {
  if (x > 0.0) {
    x += 0x1p+23;
    x -= 0x1p+23;
    x = __builtin_fabsf(x);
  }
  return x;
}

int main() {
#ifdef FE_DOWNWARD
  fesetround(FE_DOWNWARD);
  if (__builtin_signbit(foo(0.5)))
    __builtin_abort();
#endif
}