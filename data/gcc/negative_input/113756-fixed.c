int d, e, i, k, l = -8;
signed char h, j;

int bar(int n, int o, int p3) {
  int a = o - p3;
  int b = n - p3;
  int c = (int)(a + b);
  int f = -b;
  int g = (c < 0) ? -c : c;
  return (a <= f && a <= g) ? o : p3;
}

void foo(int *n, unsigned short o) {
  int p = 8896;
  for (; e >= 0; e--)
    p = 5377;
  for (; h <= 0; h++)
    for (; j <= 0; j++) {
      *n = 1611581749;
      i = bar(34, (int)(p - 5294), *n - 1611581687);
      k = (int)(i + p + 65535 + o + *n - 1611718251);
      if (k != 0)
        __builtin_abort();
    }
}

int main() {
  foo(&l, l);
  return 0;
}