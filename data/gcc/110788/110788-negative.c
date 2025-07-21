double a[1024], b[1024];

void foo(int n) {
  for (long i = 0; i < n; ++i)
    a[i] = b[i] * 3.;
}