#ifdef __sun
#if defined(__GNUC__) && !defined(__gas__)
#error "Skip test on Solaris with native assembler"
#endif
#endif

#define HAVE_512
#define AVX512CD

#include "avx512f-helper.h"

#define SIZE (AVX512F_LEN / 64)

static void CALC(long long *res, __mmask8 src) {
  int i;

  for (i = 0; i < SIZE; i++)
    res[i] = src;
}

void TEST(void) {
  int i;
  UNION_TYPE(AVX512F_LEN, i_q) res;
  long long res_ref[SIZE];
  __mmask8 src = 0;

  for (i = 0; i < SIZE; i++) {
    res.a[i] = -1;
  }

  res.x = INTRINSIC(_broadcastmb_epi64)(src);

  CALC(res_ref, src);

  if (UNION_CHECK(AVX512F_LEN, i_q)(res, res_ref))
    abort();
}