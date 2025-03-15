/* { dg-do compile } */
/* { dg-options "-O2 -mavx" } */

#include <immintrin.h>

int foo(__m256i x, __m256i y) {
  __m256i a = _mm256_andnot_si256(y, x);
  return _mm256_testz_si256(a, a);
}

int bar(__m256i x, __m256i y) {
  __m256i a = _mm256_andnot_si256(x, y);
  return _mm256_testz_si256(a, a);
}

/* { dg-final { scan-assembler-times "vptest\[ \\t\]+%" 2 } } */
/* { dg-final { scan-assembler-times "setc" 2 } } */
/* { dg-final { scan-assembler-not "vpandn" } } */
/* { dg-final { scan-assembler-not "sete" } } */