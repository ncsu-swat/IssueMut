#include "riscv_vector.h"

double f0(int8_t *restrict in, int8_t *restrict out, int n, int m,
          unsigned cond, size_t vl, double scalar) {
  vbool64_t mask = *(vbool64_t *)(in + 1000000);
  *(vbool64_t *)(out + 1000000) = mask;

  vfloat64m1_t v = *(vfloat64m1_t *)(in + 300000);
  for (size_t i = 0; i < n; i++) {
    v = __riscv_vfmv_s_f_f64m1_tu(v, (scalar + i), 3);
  }
  return __riscv_vfmv_f_s_f64m1_f64(v);
}