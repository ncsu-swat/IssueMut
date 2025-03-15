#include <math.h>

#ifndef CHECK_H
#define CHECK_H "sse4_1-check.h"
#endif

#ifndef TEST
#define TEST sse4_1_test
#endif

#include CHECK_H
#include <emmintrin.h>

void __attribute__((noinline)) __cond_swap(double *__x, double *__y) {
  __m128d x = _mm_load_sd(__x);
  __m128d y = _mm_load_sd(__y);
  __m128d min = _mm_min_sd(x, y);
  __m128d max = _mm_max_sd(x, y);
  _mm_store_sd(__x, min);
  _mm_store_sd(__y, max);
}

auto test1() {
  double nan = -0.0;
  double x = 0.0;
  __cond_swap(&nan, &x);
  return x == -0.0 && nan == 0.0;
}

auto test1r() {
  double nan = NAN;
  double x = 1.0;
  __cond_swap(&x, &nan);
  return isnan(x) && signbit(x) == 0 && nan == 1.0;
}

auto test2() {
  double nan = NAN;
  double x = -1.0;
  __cond_swap(&nan, &x);
  return isnan(x) && signbit(x) == 0 && nan == -1.0;
}

auto test2r() {
  double nan = NAN;
  double x = -1.0;
  __cond_swap(&x, &nan);
  return isnan(x) && signbit(x) == 0 && nan == -1.0;
}

auto test3() {
  double nan = -NAN;
  double x = 1.0;
  __cond_swap(&nan, &x);
  return isnan(x) && signbit(x) == 1 && nan == 1.0;
}

auto test3r() {
  double nan = -NAN;
  double x = 1.0;
  __cond_swap(&x, &nan);
  return isnan(x) && signbit(x) == 1 && nan == 1.0;
}

auto test4() {
  double nan = -NAN;
  double x = -1.0;
  __cond_swap(&nan, &x);
  return isnan(x) && signbit(x) == 1 && nan == -1.0;
}

auto test4r() {
  double nan = -NAN;
  double x = -1.0;
  __cond_swap(&x, &nan);
  return isnan(x) && signbit(x) == 1 && nan == -1.0;
}

static void TEST() {
  if (!test1() || !test1r() || !test2() || !test2r() || !test3() || !test3r() ||
      !test4() || !test4r())
    __builtin_abort();
}