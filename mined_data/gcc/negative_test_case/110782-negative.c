long foo(char *p1, short *p2, int *p3) {
  long x = (int)*p1;
  long y = (int)*p2;
  long z = *p3;

  return x + y + z;
}