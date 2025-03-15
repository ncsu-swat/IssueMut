#include "tree-vect.h"

typedef signed char schar;

__attribute__((noipa, noinline, optimize("O3"))) void
foo(const schar *a, const schar *b, schar *c, int n) {
  for (int i = 0; i < n; i++) {
    int u = __builtin_abs(a[i] - b[i]);
    c[i] = u <= 7 ? u : 7;
  }
}