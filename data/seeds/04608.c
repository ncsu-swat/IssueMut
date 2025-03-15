/* { dg-do compile { target { arm*-*-* || mips*-*-* } } } */

#include <stdint.h>
#include <stdlib.h>

int main(void) {
  void *p = main;
  if ((intptr_t)p & 1)
    abort();
  return 0;
}

/* { dg-final { scan-assembler "abort" } } */
