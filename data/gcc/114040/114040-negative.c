#if __BITINT_MAXWIDTH__ >= 8671
__attribute__((noipa)) unsigned foo(unsigned _BitInt(8671) x, unsigned y,
                                    unsigned _BitInt(512) z) {
  unsigned _BitInt(8671) r =
      x * (((y * z) >> 255) != 0);
  return r;
}
#endif

int main() {
#if __BITINT_MAXWIDTH__ >= 8671
  if (foo(1, 1, 0xfffa46471e7c2dd60000000000000000wb))
    __builtin_abort();
#endif
}