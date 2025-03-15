#include <stdarg.h>
#include <stdlib.h>

void vat(va_list param, ...) {
  va_list local;

  __builtin_va_start(local, param);

  if (__builtin_va_arg(global, int) << 1)
    abort();
}