/* PR tree-optimization/109393 */
/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

#include <stddef.h>

int foo(int *a, size_t j) {
  size_t k = j - 1;
  return a[j - 1] == a[k];
}

int foo2(int *a, size_t j) {
  size_t k = j - 5;
  return a[j - 5] == a[k];
}

int bar(int *a, size_t j) {
  size_t k = j - 1;
  return (&a[j + 1] - 2) == &a[k];
}

/* { dg-final { scan-tree-dump-times "return 1;" 3 "optimized" } } */