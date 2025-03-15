#include "riscv_vector.h"

#define RISCV_MATH_LOOPUNROLL
#define RISCV_MATH_VECTOR
typedef float float32_t;

typedef struct {
  uint16_t numTaps;
  float32_t *pState;
  float32_t *pCoeffs;
  float32_t mu;
} riscv_lms_instance_f32;

void riscv_lms_f32(const riscv_lms_instance_f32 *S, const float32_t *pSrc,
                   float32_t *pRef, float32_t *pOut, float32_t *pErr,
                   uint32_t blockSize) {
  float32_t *pState = S->pState;
  float32_t *pCoeffs = S->pCoeffs;
  float32_t *pStateCurnt;
  float32_t *px, *pb;
  float32_t mu = S->mu;
  float32_t acc, e;
  float32_t w;
  uint32_t numTaps = S->numTaps;
  uint32_t tapCnt, blkCnt;

  e = 0.0f;
  w = 0.0f;

  pStateCurnt = &(S->pState[(numTaps - 1U)]);
  blkCnt = blockSize;

  while (blkCnt > 0U) {
    *pStateCurnt++ = *pSrc++;
    px = pState;
    pb = pCoeffs;

    acc = 0.0f;
    uint32_t vblkCnt = numTaps;
    size_t l;
    vfloat32m8_t vx, vy;
    vfloat32m1_t temp00m1;
    l = __riscv_vsetvl_e32m1(1);
    temp00m1 = __riscv_vfmv_v_f_f32m1(0, l);

    tapCnt = numTaps;
    for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
      vx = __riscv_vle32_v_f32m8(px, l);
      px += l;
      vy = __riscv_vle32_v_f32m8(pb, l);
      pb += l;
      temp00m1 = __riscv_vfredusum_vs_f32m8_f32m1(
          __riscv_vfmul_vv_f32m8(vx, vy, l), temp00m1, l);
      tapCnt -= l;
    }
    acc += __riscv_vfmv_f_s_f32m1_f32(temp00m1);

    while (tapCnt > 0U) {
      acc += (*px++) * (*pb++);
      tapCnt--;
    }

    *pOut++ = acc;
    e = (float32_t)*pRef++ - acc;
    *pErr++ = e;
    w = e * mu;
    px = pState++;
    pb = pCoeffs;

    tapCnt = numTaps;
    vblkCnt = numTaps;
    for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
      vx = __riscv_vle32_v_f32m8(px, l);
      px += l;
      __riscv_vse32_v_f32m8(
          pb,
          __riscv_vfadd_vv_f32m8(__riscv_vfmul_vf_f32m8(vx, w, l),
                                 __riscv_vle32_v_f32m8(pb, l), l),
          l);
      pb += l;
      tapCnt -= l;
    }

    while (tapCnt > 0U) {
      *pb += w * (*px++);
      pb++;
      tapCnt--;
    }

    blkCnt--;
  }

  pStateCurnt = S->pState;
  tapCnt = numTaps - 1U;
  uint32_t vblkCnt = tapCnt;
  size_t l;

  for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
    __riscv_vse32_v_f32m8(pStateCurnt, __riscv_vle32_v_f32m8(pState, l), l);
    pState += l;
    pStateCurnt += l;
    tapCnt -= l;
  }

  while (tapCnt > 0U) {
    *pStateCurnt++ = *pState++;
    tapCnt--;
  }
}