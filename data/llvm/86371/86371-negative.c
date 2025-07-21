#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct S271 {
  union {
    int dummy;
  } a;
  double b;
};
struct S271 s271;
void check271va(int z, ...) {
  struct S271 arg;
  va_list ap;
  __builtin_va_start(ap, z);
  arg = __builtin_va_arg(ap, struct S271);
  long double a = __builtin_va_arg(ap, long double);
  printf("%Lf\n", a);
  if (a != 2.0L)
    printf("Fail\n");
  __builtin_va_end(ap);
}
int main(void) {
  printf("%lu\n", sizeof(s271));
  check271va(2, s271, 2.0L);
}