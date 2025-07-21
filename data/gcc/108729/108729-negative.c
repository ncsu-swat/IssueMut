#include <altivec.h>
#include <stdbool.h>
#include <stdlib.h>

bool test_denormal(double *p) {
#ifdef __powerpc64__
  double source = *p;

  
  return scalar_test_data_class(source, 3);
#else
  return true;
#endif
}

int main() {
#ifdef __powerpc64__
  
  double denormal_plus = scalar_insert_exp(0x0008000000000000ULL, 0x0ULL);
  double denormal_minus = scalar_insert_exp(0x8008000000000000ULL, 0x0ULL);
  double not_denormal = scalar_insert_exp(0x8000000000000000ULL, 1023ULL);

  if (!test_denormal(&denormal_plus))
    abort();
  if (!test_denormal(&denormal_minus))
    abort();
  if (test_denormal(&not_denormal))
    abort();
#endif
  return 0;
}