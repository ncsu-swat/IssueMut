#include <stdint.h>

void __attribute__((optimize("tree-vectorize")))
bar(unsigned int *__restrict __attribute__((aligned(16))) b,
    unsigned int *__restrict __attribute__((aligned(16))) d) {
  d[0] = __builtin_popcount(b[0]);
  d[1] = __builtin_popcount(b[1]);
  d[2] = __builtin_popcount(b[2]);
  d[3] = __builtin_popcount(b[3]);
}

void __attribute__((optimize("tree-vectorize")))
bar1(unsigned int *__restrict __attribute__((aligned(16))) b,
     unsigned int *__restrict __attribute__((aligned(16))) d) {
  d[0] = __builtin_popcount(b[0]);
  d[1] = __builtin_popcount(b[1]);
}

void __attribute__((optimize("tree-vectorize")))
bar2(unsigned long long *__restrict __attribute__((aligned(16))) b,
     unsigned long long *__restrict __attribute__((aligned(16))) d) {
  d[0] = __builtin_popcountll(b[0]);
  d[1] = __builtin_popcountll(b[1]);
}