int a, b, c, d, e;
int f() {
  c = 0;
  while (c >= 0) {
    d = 0;
    if (d <= 0) {
      e = 0;
      while (d + c + e >= 0)
        e--;
      a = 1;
      b = 0;
      while (a) {
        a *= 2;
        b++;
      }
      if (b + d >= 0)
        return 0;
    }
    c--;
  }
  return 0;
}