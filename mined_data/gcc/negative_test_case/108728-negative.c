#include <fenv.h>
#include <stdlib.h>

int main(void) {
  volatile __float128 a = __builtin_nanq(""), b = 0.0q;
  volatile int r = a < b;
  if (__builtin_isunordered(a, b))
    feraiseexcept(FE_INVALID);
  if (!fetestexcept(FE_INVALID))
    abort();
  if (r)
    abort();
  exit(0);
}