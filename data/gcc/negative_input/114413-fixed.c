#include "tree-vect.h"

int __attribute__((noipa)) foo(int *__restrict__ x, int *p, int a, int b) {
  p = __builtin_assume_aligned(p, __BIGGEST_ALIGNMENT__);
  x = __builtin_assume_aligned(x, __BIGGEST_ALIGNMENT__);

  // Load all values first
  int p0 = p[0], p1 = p[1], p2 = p[2], p3 = p[3];

  // Compute all temporary results
  int tem[4];
  tem[0] = p0 + 1 + a;
  tem[1] = p1 + 2 + b;
  tem[2] = p2 + 3 + b;
  tem[3] = p3 + 4 + a;

  // Store all results
  x[0] = tem[0];
  x[1] = tem[1];
  x[2] = tem[2];
  x[3] = tem[3];

  // Compute sum
  int sum = tem[0] + tem[1] + tem[2] + tem[3];
  return sum;
}

int x[4] __attribute__((aligned(__BIGGEST_ALIGNMENT__)));
int p[4] __attribute__((aligned(__BIGGEST_ALIGNMENT__))) = {0, 1, 2, 3};

int main() {
  check_vect();

  if (foo(x, p, 7, 13) != 56)
    abort();
  if (x[0] != 8 || x[1] != 16 || x[2] != 18 || x[3] != 14)
    abort();
  return 0;
}