void test(short *x, unsigned short *y, int n) {
  for (int i = 0; i < n; i++)
    x[i] = (short)(((int)y[i] - (int)x[i]) >> 1);
}