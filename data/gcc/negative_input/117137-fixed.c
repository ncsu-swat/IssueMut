long x[2];

int foo(int c) {
  long x0 = x[0], x1 = x[1];
  int t0 = x0 != 0;
  int t1 = x1 != 0;
  int t = t0 || t1;
  c *= t;
  return c;
}