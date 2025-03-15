#if __BITINT_MAXWIDTH__ >= 256
unsigned _BitInt(256) x;

void foo(unsigned _BitInt(256) a, unsigned _BitInt(256) b) { x = a / b; }
#endif

int main() {
#if __BITINT_MAXWIDTH__ >= 256
  foo(0xfffffffffffffffffffffc0000000000000000000004uwb,
      0x7ffffffffffffffffffffffffffuwb);
  if (x != 0x1fffffffffffffffffuwb)
    __builtin_abort();
#endif
  return 0;
}