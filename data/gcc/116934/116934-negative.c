int a;
float *b;

void foo() {
  for (; a; a--, b += 4) {
    if (b[2] > 0) {
      b[0] = b[2];
      b[1] = b[2];
    } else {
      b[0] = 0;
      b[1] = 0;
      b[2] = 0;
    }
    if (b[3] < 0)
      b[3] = 0;
  }
}