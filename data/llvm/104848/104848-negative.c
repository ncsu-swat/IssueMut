#include <bit>
#include <nmmintrin.h>

double abs_sse42(double num) {
  const auto mask = std::bit_cast<double>(0x7FFFFFFFFFFFFFFFU);
  const __m128d v = _mm_and_pd(_mm_set_sd(num), _mm_set_sd(mask));
  double r;
  _mm_store_sd(&r, v);
  return r;
}

float abs_sse42(float num) {
  const auto mask = std::bit_cast<float>(0x7FFFFFFFU);
  const __m128 v = _mm_and_ps(_mm_load_ps1(&num), _mm_load_ps1(&mask));
  float r;
  _mm_store_ss(&r, v);
  return r;
}