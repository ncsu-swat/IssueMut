#include <stdint-gcc.h>

#define COND_REDUCTION(TYPE)                                                   \
  TYPE foo##TYPE(TYPE *restrict a, TYPE *restrict b, int loop_size) {          \
    TYPE result = 0;                                                           \
    for (int i = 0; i < loop_size; i++) {                                      \
      if (!(b[i] <= a[i]))                                                     \
        continue;                                                              \
      result += a[i];                                                          \
    }                                                                          \
    return result;                                                             \
  }

COND_REDUCTION(int8_t)
COND_REDUCTION(int16_t)
COND_REDUCTION(int32_t)
COND_REDUCTION(int64_t)
COND_REDUCTION(uint8_t)
COND_REDUCTION(uint16_t)
COND_REDUCTION(uint32_t)
COND_REDUCTION(uint64_t)
COND_REDUCTION(_Float16)
COND_REDUCTION(float)
COND_REDUCTION(double)