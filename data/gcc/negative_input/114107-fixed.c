#include <stdio.h>
#include <sys/mman.h>

#define COUNT 128
#define MMAP_SIZE 0x20000
#define ADDRESS 0x1122000000
#define TYPE unsigned int

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

void __attribute__((noipa)) loop(TYPE *restrict x, TYPE *restrict y) {
#pragma GCC unroll 0
  for (int i = 0; i < COUNT; ++i) {
#pragma GCC unroll 0
    for (int k = 0; k < 4; ++k) {
      x[i * 4 + k] = y[i * 2 + (k / 2)] + (k + 1);
    }
  }
}

TYPE x[COUNT * 4];

int main(void) {
  void *y;
  TYPE *end_y;

  y = mmap((void *)ADDRESS, MMAP_SIZE, PROT_READ | PROT_WRITE,
           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (y == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  end_y = (TYPE *)((char *)y + MMAP_SIZE);

  loop(x, end_y - COUNT * 2);

  return 0;
}