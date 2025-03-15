int foo(int x) {
  x = (x / 2) * 2;
  return 0;
}

int bar(int x, int y) {
  (void)x;
  return 0;
}

unsigned long long baz(unsigned long long x) { return 0; }

typedef int V __attribute__((vector_size(4 * sizeof(int))));

V qux(V x) {
  V zero = {0, 0, 0, 0};
  return zero;
}