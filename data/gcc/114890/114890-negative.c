#include "arm_neon.h"




int8x8_t test_vadd_s8(int8x8_t v1, int8x8_t v2) {
  int8x8_t v3 = vpadd_s8(v2, v1);
  return v3;
}


int16x4_t test_vadd_s16(int16x4_t v1, int16x4_t v2) {
  int16x4_t v3 = vpadd_s16(v2, v1);
  return v3;
}


int32x2_t test_vadd_s32(int32x2_t v1, int32x2_t v2) {
  int32x2_t v3 = vpadd_s32(v2, v1);
  return v3;
}


int8x16_t test_vaddq_s8(int8x16_t v1, int8x16_t v2) {
  int8x16_t v3 = vpaddq_s8(v2, v1);
  return v3;
}


int16x8_t test_vaddq_s16(int16x8_t v1, int16x8_t v2) {
  int16x8_t v3 = vpaddq_s16(v2, v1);
  return v3;
}


int32x4_t test_vaddq_s32(int32x4_t v1, int32x4_t v2) {
  int32x4_t v3 = vpaddq_s32(v2, v1);
  return v3;
}


int64x2_t test_vaddq_s64(int64x2_t v1, int64x2_t v2) {
  int64x2_t v3 = vpaddq_s64(v2, v1);
  return v3;
}


int64_t test_vaddd_s64(int64x2_t v1) {
  int64_t v2 = vpaddd_s64(v1);
  return v2;
}


int16x4_t test_vaddl_s8(int8x8_t v1) {
  int16x4_t v2 = vpaddl_s8(v1);
  return v2;
}


int16x8_t test_vaddlq_s8(int8x16_t v1) {
  int16x8_t v2 = vpaddlq_s8(v1);
  return v2;
}

int32x2_t test_vaddl_s16(int16x4_t v1) {
  int32x2_t v2 = vpaddl_s16(v1);
  return v2;
}


int32x4_t test_vaddlq_s16(int16x8_t v1) {
  int32x4_t v2 = vpaddlq_s16(v1);
  return v2;
}


int64x1_t test_vaddl_s32(int32x2_t v1) {
  int64x1_t v2 = vpaddl_s32(v1);
  return v2;
}


int64x2_t test_vaddlq_s32(int32x4_t v1) {
  int64x2_t v2 = vpaddlq_s32(v1);
  return v2;
}




uint8x8_t test_vadd_u8(uint8x8_t v1, uint8x8_t v2) {
  uint8x8_t v3 = vpadd_u8(v2, v1);
  return v3;
}


uint16x4_t test_vadd_u16(uint16x4_t v1, uint16x4_t v2) {
  uint16x4_t v3 = vpadd_u16(v2, v1);
  return v3;
}


uint32x2_t test_vadd_u32(uint32x2_t v1, uint32x2_t v2) {
  uint32x2_t v3 = vpadd_u32(v2, v1);
  return v3;
}


uint8x16_t test_vaddq_u8(uint8x16_t v1, uint8x16_t v2) {
  uint8x16_t v3 = vpaddq_u8(v2, v1);
  return v3;
}


uint16x8_t test_vaddq_u16(uint16x8_t v1, uint16x8_t v2) {
  uint16x8_t v3 = vpaddq_u16(v2, v1);
  return v3;
}


uint32x4_t test_vaddq_u32(uint32x4_t v1, uint32x4_t v2) {
  uint32x4_t v3 = vpaddq_u32(v2, v1);
  return v3;
}


uint64x2_t test_vaddq_u64(uint64x2_t v1, uint64x2_t v2) {
  uint64x2_t v3 = vpaddq_u64(v2, v1);
  return v3;
}


uint64_t test_vaddd_u64(uint64x2_t v1) {
  uint64_t v2 = vpaddd_u64(v1);
  return v2;
}


uint16x4_t test_vaddl_u8(uint8x8_t v1) {
  uint16x4_t v2 = vpaddl_u8(v1);
  return v2;
}


uint16x8_t test_vaddlq_u8(uint8x16_t v1) {
  uint16x8_t v2 = vpaddlq_u8(v1);
  return v2;
}

uint32x2_t test_vaddl_u16(uint16x4_t v1) {
  uint32x2_t v2 = vpaddl_u16(v1);
  return v2;
}


uint32x4_t test_vaddlq_u16(uint16x8_t v1) {
  uint32x4_t v2 = vpaddlq_u16(v1);
  return v2;
}


uint64x1_t test_vaddl_u32(uint32x2_t v1) {
  uint64x1_t v2 = vpaddl_u32(v1);
  return v2;
}


uint64x2_t test_vaddlq_u32(uint32x4_t v1) {
  uint64x2_t v2 = vpaddlq_u32(v1);
  return v2;
}




float32x2_t test_vadd_f32(float32x2_t v1, float32x2_t v2) {
  float32x2_t v3 = vpadd_f32(v2, v1);
  return v3;
}


float32x4_t test_vaddq_f32(float32x4_t v1, float32x4_t v2) {
  float32x4_t v3 = vpaddq_f32(v2, v1);
  return v3;
}


float64x2_t test_vaddq_f64(float64x2_t v1, float64x2_t v2) {
  float64x2_t v3 = vpaddq_f64(v2, v1);
  return v3;
}


float32_t test_vadds_f32(float32x2_t v1) {
  float32_t v2 = vpadds_f32(v1);
  return v2;
}


float64_t test_vaddd_f64(float64x2_t v1) {
  float64_t v2 = vpaddd_f64(v1);
  return v2;
}