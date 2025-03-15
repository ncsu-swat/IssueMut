#include "tree-vect.h"

extern void abort(void);

unsigned char a[64];
short b[88];

void __attribute__((noinline))
test(unsigned char *__restrict__ dst, short *__restrict__ tptr) {
  int i;
  int main_iters = (8 / 4) * 4; // Align to vector size

  // Main vectorizable loop
  for (i = 0; i < main_iters; i++) {
    dst[0] = (tptr[0] - tptr[0 + 3]);
    dst[1] = (tptr[1] - tptr[1 + 3]);
    dst[2] = (tptr[2] - tptr[2 + 3]);
    dst[3] = (tptr[3] - tptr[3 + 3]);
    dst[4] = (tptr[4] - tptr[4 + 3]);
    dst[5] = (tptr[5] - tptr[5 + 3]);
    dst[6] = (tptr[6] - tptr[6 + 3]);
    dst[7] = (tptr[7] - tptr[7 + 3]);
    dst += 8;
    tptr += 11;
  }

  // Epilogue handling
  for (; i < 8; i++) {
    dst[0] = (tptr[0] - tptr[0 + 3]);
    dst[1] = (tptr[1] - tptr[1 + 3]);
    dst[2] = (tptr[2] - tptr[2 + 3]);
    dst[3] = (tptr[3] - tptr[3 + 3]);
    dst[4] = (tptr[4] - tptr[4 + 3]);
    dst[5] = (tptr[5] - tptr[5 + 3]);
    dst[6] = (tptr[6] - tptr[6 + 3]);
    dst[7] = (tptr[7] - tptr[7 + 3]);
    dst += 8;
    tptr += 11;
  }
}

int main() {
  int i;

  check_vect();

  for (i = 0; i < 88; ++i) {
    b[i] = i;
    __asm__ volatile("");
  }

  test(a, b);

  for (i = 0; i < 64; ++i)
    if (a[i] != 253)
      abort();

  return 0;
}