#define AVX512VL
#include "avx512f-helper.h"

typedef __attribute__((__vector_size__(16))) unsigned V;

short s;

V foo() {
  typedef __attribute__((__vector_size__(16))) int SV;
  const V C = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
  V a = -(V){0, 0, 0, 1};
  V s_v = {s, s, s, s};
  return (V)((SV)(a + C) > (SV)(s_v + C));
}

void test_128() {
  V x = foo();
  if (x[0] != 0 || x[1] != 0 || x[2] != 0 || x[3] != 0xffffffff)
    __builtin_abort();
}

void test_256() {}