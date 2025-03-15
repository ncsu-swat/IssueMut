int __GIMPLE() f(int a, int b, int c, int d, int e) {
  int ff;
  int gg;
  int res;
  if (a == b) {
    ff = a;
    gg = d;
  } else {
    ff = e;
    gg = b;
  }
  res = ff + gg;
  return res;
}