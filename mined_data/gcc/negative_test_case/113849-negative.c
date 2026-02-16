signed char c;
unsigned _BitInt(512) b;

__attribute__((noipa)) void foo(unsigned _BitInt(511) a, int *x) {
  int z = (a << 510) <= (unsigned _BitInt(511))b;
  *x = z + c;
}

int main() {
  int x;
  foo(2, &x);
  if (x != 1)
    __builtin_abort();
  return 0;
}