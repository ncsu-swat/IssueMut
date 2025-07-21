long foo(signed char *p1, short *p2, int *p3) {
  long x = *p1;
  long y = *p2;
  long z = *p3;

  return x + y + z;
}