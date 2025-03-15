/* { dg-do run { target { powerpc*-*-* } } } */
/* { dg-require-effective-target has_arch_ppc64 } */
/* { dg-require-effective-target p9vector_hw } */
/* { dg-options "-mdejagnu-cpu=power9" } */

#include <altivec.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool test_denormal(double *p) {
  double source = *p;

  /*
    0x40    Test for NaN
    0x20    Test for +Infinity
    0x10    Test for -Infinity
    0x08    Test for +Zero
    0x04    Test for -Zero
    0x02    Test for +Denormal
    0x01    Test for -Denormal
  */
  return scalar_test_data_class(source, 3);
}

int main() {
  double denormal_plus;
  double denormal_minus;
  double not_denormal;

  union {
    uint64_t u;
    double d;
  } u;

  u.u = 0x0008000000000000ULL;
  denormal_plus = u.d;

  u.u = 0x8008000000000000ULL;
  denormal_minus = u.d;

  u.u = 0x8000000000000000ULL;
  not_denormal = u.d;

  if (!test_denormal(&denormal_plus))
    abort();
  if (!test_denormal(&denormal_minus))
    abort();
  if (test_denormal(&not_denormal))
    abort();
  return 0;
}