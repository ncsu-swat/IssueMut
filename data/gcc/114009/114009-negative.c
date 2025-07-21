int foo(int x) {
  x = (x / 2) * 2;
  return x ? 0 : x;
}

int bar(int x, int y) {
  (void)x;
  return y ? 0 : y;
}

unsigned long long baz(unsigned long long x) { return x ? 0 : x; }

typedef int V __attribute__((vector_size(4 * sizeof(int))));

V qux(V x) { return (x == 0) ? x : (V){0}; }