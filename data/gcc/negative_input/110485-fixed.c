#include <math.h>

extern double bar(double a, double p);

double a[1024];
double b[1024];

void foo(int n) {
  for (int i = 0; i < n; ++i)
    a[i] = bar(b[i], 71.2);
}