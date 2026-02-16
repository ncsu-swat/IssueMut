int f(int *a(), int *b, int *c, int *d) {
  int s = 0;
  for (int *i = a(); i < b; ++i, ++c)
    s += *c * d[*i];
  return s;
}