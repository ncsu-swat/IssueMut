int printf(char *, ...);
int a, j, n, b, c, o, d, g, h;
int e[8];
long f[8][6];
void l() {
  o = -27;
  for (; o; o++) {
    *e = 1;
    if (a >= n) {
      d = 0;
      for (; d <= 7; d++)
        e[d] = c;
    }
  }
  j = 0;
  for (; j < 8; j++) {
    g = 0;
    for (; g < 2; g++) {
      h = 1;
      for (; h < 3; h++)
        f[j][g * 2 + h] = 1;
    }
  }
  long *m = &f[1][1];
  *m = 0;
}
int main() {
  l();
  b = f[0][1];
  printf("b: %d\n", b);
}