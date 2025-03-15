int a;
long b;
signed c;
short d;
short i;

void foo(void) {
  int k[3] = {0};
  int *l = &a;
  d = 0;
  for (; c; c--) {
    i = 0;
    for (; i <= 9; i++) {
      b = 1;
      for (; b <= 4; b++) {
        int temp = (k[0] != 0) ? 0 : 1;
        k[0] = temp;
      }
      *l |= k[d];
    }
  }
}