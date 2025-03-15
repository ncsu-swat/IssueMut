#if __BITINT_MAXWIDTH__ >= 1024
unsigned _BitInt(1024) a = -5wb;

__attribute__((noipa)) void foo(unsigned _BitInt(1024) x) {
  unsigned _BitInt(1024) temp = a;
  temp *= x;
  a = temp;
}
#else
int a = 30;

void foo(int) {}
#endif

int main() {
  foo(-6wb);
  if (a != 30wb)
    __builtin_abort();
  return 0;
}