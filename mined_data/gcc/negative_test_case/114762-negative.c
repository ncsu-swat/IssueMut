#if __BITINT_MAXWIDTH__ >= 255
__attribute__((__noipa__)) signed _BitInt(255)
    foo(signed _BitInt(255) a, signed _BitInt(66) b) {
  return a / b;
}
#endif

int main() {
#if __BITINT_MAXWIDTH__ >= 255
  if (foo(1, (_BitInt(66))(-0xffffffffffffffffwb - 1wb)))
    __builtin_abort();
#endif
}