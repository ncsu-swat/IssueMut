void foo(int *a, short *__restrict b, int *c) {
  for (int i = 0; i < 16; i += 8)
    for (int j = 0; j < 8; j++)
      b[i + j] = c[i + j] + a[i + j];
}

void foo1(int *a, short *__restrict b, int *c) {
  for (int i = 0; i < 8; i++)
    b[i] = c[i] + a[i];
}