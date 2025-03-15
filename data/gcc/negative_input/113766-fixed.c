/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_zvfh -mabi=lp64 -O3" } */

#include "riscv_vector.h"

void test() {
  vuint32m1_t a1, a2, a3;
  vbool32_t mask;
  size_t vl = 0;

  __riscv_vand(a2, a3, vl); /* { dg-error {no matching function call to
                               '__riscv_vand' with empty args} } */
  __riscv_vand_tu(a1, mask, a2, a3,
                  vl); /* { dg-error {no matching function call to
                          '__riscv_vand_tu' with empty args} } */
  __riscv_vand_tumu(a1, mask, a2, a3,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vand_tumu' with empty args} } */

  __riscv_vcompress(a1, mask, a2,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vcompress' with empty args} } */
  __riscv_vcompress_tu(a1, a2, mask, a3,
                       vl); /* { dg-error {no matching function call to
                               '__riscv_vcompress_tu' with empty args} } */

  a1 = __riscv_vcpop(a2, vl); /* { dg-error {no matching function call to
                                 '__riscv_vcpop' with empty args} } */

  __riscv_vdiv(a1, a2, a3, vl); /* { dg-error {no matching function call to
                                   '__riscv_vdiv' with empty args} } */
  __riscv_vdiv_tu(a1, mask, a2, a3,
                  vl); /* { dg-error {no matching function call to
                          '__riscv_vdiv_tu' with empty args} } */
  __riscv_vdiv_tumu(a1, mask, a2, a3,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vdiv_tumu' with empty args} } */

  vfloat32m1_t f1, f2, f3;
  __riscv_vfabs(f2, vl); /* { dg-error {no matching function call to
                            '__riscv_vfabs' with empty args} } */
  __riscv_vfabs_tu(f1, mask, f2,
                   vl); /* { dg-error {no matching function call to
                           '__riscv_vfabs_tu' with empty args} } */
  __riscv_vfabs_tumu(f1, mask, f2,
                     vl); /* { dg-error {no matching function call to
                             '__riscv_vfabs_tumu' with empty args} } */

  __riscv_vfadd(f1, f2, f3, vl); /* { dg-error {no matching function call to
                                    '__riscv_vfadd' with empty args} } */
  __riscv_vfadd_tu(f1, mask, f2, f3,
                   vl); /* { dg-error {no matching function call to
                           '__riscv_vfadd_tu' with empty args} } */
  __riscv_vfadd_tumu(f1, mask, f2, f3,
                     vl); /* { dg-error {no matching function call to
                             '__riscv_vfadd_tumu' with empty args} } */

  vuint32m1_t mres;
  a1 = __riscv_vfclass(f1, vl); /* { dg-error {no matching function call to
                                   '__riscv_vfclass' with empty args} } */
  a1 = __riscv_vfclass_tu(a1, mask, f2,
                          vl); /* { dg-error {no matching function call to
                                  '__riscv_vfclass_tu' with empty args} } */
  a1 = __riscv_vfclass_tumu(a1, mask, f2,
                            vl); /* { dg-error {no matching function call to
                                    '__riscv_vfclass_tumu' with empty args} } */

  __riscv_vfcvt_x(f1, vl); /* { dg-error {no matching function call to
                              '__riscv_vfcvt_x' with empty args} } */
  __riscv_vfcvt_x_tu(a1, mask, f2,
                     vl); /* { dg-error {no matching function call to
                             '__riscv_vfcvt_x_tu' with empty args} } */
  __riscv_vfcvt_x_tumu(a1, mask, f2,
                       vl); /* { dg-error {no matching function call to
                               '__riscv_vfcvt_x_tumu' with empty args} } */

  size_t idx =
      __riscv_vfirst(mask, vl); /* { dg-error {no matching function call to
                                   '__riscv_vfirst' with empty args} } */

  __riscv_vfmadd(f1, f2, f3, vl); /* { dg-error {no matching function call to
                                     '__riscv_vfmadd' with empty args} } */
  __riscv_vfmadd_tu(f1, mask, f2, f3,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vfmadd_tu' with empty args} } */
  __riscv_vfmadd_tumu(f1, mask, f2, f3,
                      vl); /* { dg-error {no matching function call to
                              '__riscv_vfmadd_tumu' with empty args} } */

  __riscv_vfmerge(f1, mask, f2, f3,
                  vl); /* { dg-error {no matching function call to
                          '__riscv_vfmerge' with empty args} } */
  __riscv_vfmerge_tu(f1, f2, mask, f3,
                     vl); /* { dg-error {no matching function call to
                             '__riscv_vfmerge_tu' with empty args} } */

  __riscv_vfncvt_x(f1, vl); /* { dg-error {no matching function call to
                               '__riscv_vfncvt_x' with empty args} } */
  __riscv_vfncvt_x_tu(a1, mask, f2,
                      vl); /* { dg-error {no matching function call to
                              '__riscv_vfncvt_x_tu' with empty args} } */
  __riscv_vfncvt_x_tumu(a1, mask, f2,
                        vl); /* { dg-error {no matching function call to
                                '__riscv_vfncvt_x_tumu' with empty args} } */

  __riscv_vfrec7(f1, vl); /* { dg-error {no matching function call to
                             '__riscv_vfrec7' with empty args} } */
  __riscv_vfrec7_tu(f1, mask, f2,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vfrec7_tu' with empty args} } */
  __riscv_vfrec7_tumu(f1, mask, f2,
                      vl); /* { dg-error {no matching function call to
                              '__riscv_vfrec7_tumu' with empty args} } */

  __riscv_vfrsqrt7(f1, vl); /* { dg-error {no matching function call to
                               '__riscv_vfrsqrt7' with empty args} } */
  __riscv_vfrsqrt7_tu(f1, mask, f2,
                      vl); /* { dg-error {no matching function call to
                              '__riscv_vfrsqrt7_tu' with empty args} } */
  __riscv_vfrsqrt7_tumu(f1, mask, f2,
                        vl); /* { dg-error {no matching function call to
                                '__riscv_vfrsqrt7_tumu' with empty args} } */

  __riscv_vfsgnjn(f1, f2, f3, vl); /* { dg-error {no matching function call to
                                      '__riscv_vfsgnjn' with empty args} } */
  __riscv_vfsgnjn_tu(f1, mask, f2, f3,
                     vl); /* { dg-error {no matching function call to
                             '__riscv_vfsgnjn_tu' with empty args} } */
  __riscv_vfsgnjn_tumu(f1, mask, f2, f3,
                       vl); /* { dg-error {no matching function call to
                               '__riscv_vfsgnjn_tumu' with empty args} } */

  __riscv_vfslide1down(f1, f2,
                       vl); /* { dg-error {no matching function call to
                               '__riscv_vfslide1down' with empty args} } */
  __riscv_vfslide1down_tu(
      f1, mask, f2, f3, vl); /* { dg-error {no matching function call to
                                '__riscv_vfslide1down_tu' with empty args} } */
  __riscv_vfslide1down_tumu(
      f1, mask, f2, f3,
      vl); /* { dg-error {no matching function call to
              '__riscv_vfslide1down_tumu' with empty args} } */

  vfloat64m1_t f64_1, f64_2, f64_3;
  __riscv_vfwmul(f64_1, f2, f3, vl); /* { dg-error {no matching function call to
                                        '__riscv_vfwmul' with empty args} } */
  __riscv_vfwmul_tu(f64_1, mask, f2, f3,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vfwmul_tu' with empty args} } */
  __riscv_vfwmul_tumu(f64_1, mask, f2, f3,
                      vl); /* { dg-error {no matching function call to
                              '__riscv_vfwmul_tumu' with empty args} } */

  uint32_t *ptr;
  __riscv_vle32_v_u32m1(ptr, vl); /* { dg-error {no matching function call to
                                     '__riscv_vle32' with empty args} } */
  __riscv_vle32_tu(a1, mask, ptr,
                   vl); /* { dg-error {no matching function call to
                           '__riscv_vle32_tu' with empty args} } */
  __riscv_vle32_tumu(a1, mask, ptr,
                     vl); /* { dg-error {no matching function call to
                             '__riscv_vle32_tumu' with empty args} } */

  int64_t stride = 4;
  __riscv_vlse64_v_i64m1((int64_t *)ptr, stride,
                         vl); /* { dg-error {no matching function call to
                                 '__riscv_vlse64' with empty args} } */
  __riscv_vlse64_tu((int64_t *)ptr, mask, (int64_t *)ptr, stride,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vlse64_tu' with empty args} } */
  __riscv_vlse64_tumu((int64_t *)ptr, mask, (int64_t *)ptr, stride,
                      vl); /* { dg-error {no matching function call to
                              '__riscv_vlse64_tumu' with empty args} } */

  vbool32_t m1;
  m1 = __riscv_vmfeq(f1, f2, vl); /* { dg-error {no matching function call to
                                     '__riscv_vmfeq' with empty args} } */

  a1 = __riscv_vreinterpret_u8m1(
      a2); /* { dg-error {no matching function call to
              '__riscv_vreinterpret_u8m1' with empty args} } */

  __riscv_vfredosum(f1, f2, vl); /* { dg-error {no matching function call to
                                    '__riscv_vfredosum' with empty args} } */
  __riscv_vfredosum_tu(f1, f2, f3,
                       vl); /* { dg-error {no matching function call to
                               '__riscv_vfredosum_tu' with empty args} } */

  __riscv_vaadd(a1, a2, a3, vl); /* { dg-error {no matching function call to
                                    '__riscv_vaadd' with empty args} } */

  __riscv_vaaddu(a1, a2, a3, vl); /* { dg-error {no matching function call to
                                     '__riscv_vaaddu' with empty args} } */

  __riscv_vadc(a1, a2, a3, vl); /* { dg-error {no matching function call to
                                   '__riscv_vadc' with empty args} } */

  __riscv_vnmsac(a1, a2, a3, vl); /* { dg-error {no matching function call to
                                     '__riscv_vnmsac' with empty args} } */

  __riscv_vnsrl(a1, a2, 1, vl); /* { dg-error {no matching function call to
                                   '__riscv_vnsrl' with empty args} } */

  __riscv_vfnmadd(f1, f2, f3, vl); /* { dg-error {no matching function call to
                                      '__riscv_vfnmadd' with empty args} } */

  __riscv_vfwsub_vv(f64_1, f2, f3,
                    vl); /* { dg-error {no matching function call to
                            '__riscv_vfwsub_vv' with empty args} } */

  __riscv_vfwredosum(f64_1, f64_2,
                     vl); /* { dg-error {no matching function call to
                             '__riscv_vfwredosum' with empty args} } */
}