#include <stdint.h>

#define DEF_LOOP(OLD_TYPE, NEW_TYPE)                                           \
  void __attribute__((noipa)) test_##OLD_TYPE##_2_##NEW_TYPE(                  \
      NEW_TYPE *__restrict r, OLD_TYPE *__restrict a, NEW_TYPE b,              \
      int8_t *__restrict pred, int n) {                                        \
    for (int i = 0; i < n; ++i) {                                              \
      r[i] = pred[i] ? (NEW_TYPE)a[i] : b;                                     \
    }                                                                          \
  }

/* INT -> narrower-INT */
#define TEST_ALL_X2X_NARROWER(T) T(int16_t, int8_t)

TEST_ALL_X2X_NARROWER(DEF_LOOP)