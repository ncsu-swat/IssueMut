void foo(int x, int y, int z, int d, int *buf) {
  for (int i = z; i < y - z; ++i) {
    int base = i * x;
    for (int j = 0; j < d; ++j) {
      int src = base + (x - z - 1 - j);
      int dst = base + (x - z + j);
      buf[dst] = buf[src];
    }
  }
}

void bar(int x, int y, int z, int d, int *buf) {
  for (int i = 0; i < d; ++i) {
    int base_src = (y - z - 1 - i) * x;
    int base_dst = (y - z + i) * x;
    for (int j = z; j < x - z; ++j) {
      buf[j + base_dst] = buf[j + base_src];
    }
  }
}

__attribute__((noipa)) void baz(int x, int y, int d, int *buf) {
  foo(x, y, 0, d, buf);
  bar(x, y, 0, d, buf);
}

int main(void) {
  int a[] = {1, 2, 3};
  baz(1, 2, 1, a);

  for (int i = 0; i < 3; i++)
    if (a[i] != 1)
      __builtin_abort();
}