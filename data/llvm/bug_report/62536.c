#include <stdint.h>

int param_std(int *foo) {
  int temp = *foo;
  *foo = 1;
  return temp + sizeof(foo);
}

int param_ptr32(int *__ptr32 __uptr bar) {
  int temp = *bar;
  *bar = 2;
  return temp + sizeof(bar);
}

int emulate_ptr32(uint32_t baz) {
  uint64_t baz64 = baz;
  int *bazptr = (int *)baz64;
  int temp = *bazptr;
  *bazptr = 3;
  return temp + sizeof(baz);
}