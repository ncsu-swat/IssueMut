#include "riscv_vector.h"
#include <string.h>

void test_vbool1_then_vbool2(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1;
  vbool2_t v2;
  memcpy(&v1, in, sizeof(v1));
  memcpy(&v2, in, sizeof(v2));

  memcpy(out + 100, &v1, sizeof(v1));
  memcpy(out + 200, &v2, sizeof(v2));
}

void test_vbool1_then_vbool4(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1;
  vbool4_t v2;
  memcpy(&v1, in, sizeof(v1));
  memcpy(&v2, in, sizeof(v2));

  memcpy(out + 100, &v1, sizeof(v1));
  memcpy(out + 200, &v2, sizeof(v2));
}

void test_vbool1_then_vbool8(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1;
  vbool8_t v2;
  memcpy(&v1, in, sizeof(v1));
  memcpy(&v2, in, sizeof(v2));

  memcpy(out + 100, &v1, sizeof(v1));
  memcpy(out + 200, &v2, sizeof(v2));
}

void test_vbool1_then_vbool16(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1;
  vbool16_t v2;
  memcpy(&v1, in, sizeof(v1));
  memcpy(&v2, in, sizeof(v2));

  memcpy(out + 100, &v1, sizeof(v1));
  memcpy(out + 200, &v2, sizeof(v2));
}

void test_vbool1_then_vbool32(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1;
  vbool32_t v2;
  memcpy(&v1, in, sizeof(v1));
  memcpy(&v2, in, sizeof(v2));

  memcpy(out + 100, &v1, sizeof(v1));
  memcpy(out + 200, &v2, sizeof(v2));
}

void test_vbool1_then_vbool64(int8_t *restrict in, int8_t *restrict out) {
  vbool1_t v1;
  vbool64_t v2;
  memcpy(&v1, in, sizeof(v1));
  memcpy(&v2, in, sizeof(v2));

  memcpy(out + 100, &v1, sizeof(v1));
  memcpy(out + 200, &v2, sizeof(v2));
}