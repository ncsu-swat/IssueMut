#include <immintrin.h>

__m512bh cvttest(__mmask32 k, __m512 a, __m512 b) {
  return _mm512_maskz_cvtne2ps_pbh(k, b, a);
}

__m256bh cvttest2(__mmask16 k, __m256 a, __m256 b) {
  return _mm256_maskz_cvtne2ps_pbh(k, b, a);
}

__m128bh cvttest3(__mmask8 k, __m128 a, __m128 b) {
  return _mm_maskz_cvtne2ps_pbh(k, b, a);
}