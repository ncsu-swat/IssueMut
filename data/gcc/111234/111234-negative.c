#include "riscv_vector.h"


int32_t foo1(void *base, size_t vl) {
  volatile vint32m1_t v = *(vint32m1_t *)base;
  int32_t scalar = __riscv_vmv_x_s_i32m1_i32(v);
  return scalar;
}


int32_t foo2(void *base, size_t vl) {
  volatile vint32mf2_t v = *(vint32mf2_t *)base;
  int32_t scalar = __riscv_vmv_x_s_i32mf2_i32(v);
  return scalar;
}


int32_t foo3(int32_t *base, size_t vl) {
  volatile vint32m1_t v = *(vint32m1_t *)(base + 1);
  int32_t scalar = __riscv_vmv_x_s_i32m1_i32(v);
  return scalar;
}


int32_t foo4(void *base, size_t vl) {
  volatile vint32m1_t v = *(vint32m1_t *)base;
  v = __riscv_vadd_vv_i32m1(v, v, vl);
  int32_t scalar = __riscv_vmv_x_s_i32m1_i32(v);
  volatile vint32m2_t new_v = __riscv_vmv_v_x_i32m2(scalar, vl);
  scalar = __riscv_vmv_x_s_i32m2_i32(new_v);
  return scalar;
}


float foo5(int32_t *base, size_t vl) {
  volatile vint32m1_t v = *(vint32m1_t *)(base + 1);
  int32_t scalar = __riscv_vmv_x_s_i32m1_i32(v);
  return *(float *)&scalar;
}