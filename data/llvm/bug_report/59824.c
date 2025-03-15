// RUN: %clang_cc1 -fsyntax-only -verify %s

#include <stdarg.h>

void a(const char *a, ...) __attribute__((format(printf, 1, 2))); // no-error

__attribute__((format(printf, 1, 2))) void
forward_fixed(const char *fmt, _Bool b, char i, short j, int k, float l,
              double m) { // expected-warning{{GCC requires a function with the
                          // 'format' attribute to be variadic}}
  forward_fixed(fmt, b, i, j, k, l, m);
  a(fmt, b, i, j, k, l, m);
}
