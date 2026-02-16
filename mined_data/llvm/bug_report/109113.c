#include "stdio.h"
#include <vecintrin.h>
typedef unsigned char uv16qi __attribute__((vector_size(16)));
typedef unsigned int uv4si __attribute__((vector_size(16)));
typedef unsigned long long uv2di __attribute__((vector_size(16)));

int main() {
  const uv2di r2r1 = {0x1C6E41596, 0x154442BD4};
  uv2di v1 = {7381244131595332141, 2315514454429938015};
  uv16qi part1 = {97, 116, 115, 32,  109, 111, 114, 102,
                  32, 115, 101, 110, 105, 108, 32,  100};
  uv2di result = (uv2di)vec_gfmsum_accum_128(r2r1, v1, part1);
  printf("value 1: %llu\n value 2: %llu\n", result[0], result[1]);
  return 0;
}