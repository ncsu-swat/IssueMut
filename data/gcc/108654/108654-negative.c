#include "riscv_vector.h"

void test_vbool1_then_vbool2(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1 = *(vbool1_t *)in;
  vbool2_t v2 = *(volatile vbool2_t *)in;

  *(vbool1_t *)(out + 100) = v1;
  *(vbool2_t *)(out + 200) = v2;
}

void test_vbool1_then_vbool4(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1 = *(vbool1_t *)in;
  vbool4_t v2 = *(volatile vbool4_t *)in;

  *(vbool1_t *)(out + 100) = v1;
  *(vbool4_t *)(out + 200) = v2;
}

void test_vbool1_then_vbool8(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1 = *(vbool1_t *)in;
  vbool8_t v2 = *(volatile vbool8_t *)in;

  *(vbool1_t *)(out + 100) = v1;
  *(vbool8_t *)(out + 200) = v2;
}

void test_vbool1_then_vbool16(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1 = *(vbool1_t *)in;
  vbool16_t v2 = *(volatile vbool16_t *)in;

  *(vbool1_t *)(out + 100) = v1;
  *(vbool16_t *)(out + 200) = v2;
}

void test_vbool1_then_vbool32(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1 = *(vbool1_t *)in;
  vbool32_t v2 = *(volatile vbool32_t *)in;

  *(vbool1_t *)(out + 100) = v1;
  *(vbool32_t *)(out + 200) = v2;
}

void test_vbool1_then_vbool64(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1 = *(vbool1_t *)in;
  vbool64_t v2 = *(volatile vbool64_t *)in;

  *(vbool1_t *)(out + 100) = v1;
  *(vbool64_t *)(out + 200) = v2;
}