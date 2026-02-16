void foo(int x, int y, int z, int d, int *buf) {
  for (int i = z; i < y - z; ++i) {
    int base_idx = i * x + x - z;
    for (int j = 0; j < d; ++j)
      
      buf[base_idx + j] = buf[base_idx - 1 - j];
  }
}

void bar(int x, int y, int z, int d, int *buf) {
  for (int i = 0; i < d; ++i) {
    int base_dst_idx = (y - z + i) * x;
    int base_src_idx = (y - z - 1 - i) * x;
    for (int j = z; j < x - z; ++j)
      
      buf[j + base_dst_idx] = buf[j + base_src_idx];
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