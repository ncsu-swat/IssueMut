/* { dg-require-effective-target int128 } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-maltivec -mno-vsx" } */

#include <altivec.h>

extern vector signed long long res_vslll;
extern unsigned long long aull[2];

void testVectorInt128Pack() {
  res_vslll = __builtin_pack_vector_longlong(
      aull[0], aull[1]); /* { dg-error "'__builtin_pack_vector_longlong'
                            requires the '-mvsx' option" } */
}