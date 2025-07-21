void test_builtin_clzg(unsigned char uc, unsigned short us, unsigned int ui,
                       unsigned long ul, unsigned long long ull,
                       unsigned __int128 ui128, unsigned _BitInt(128) ubi128,
                       signed char sc, short s, int i) {
  volatile int lz;
  lz = __builtin_clz(uc);

  lz = __builtin_clz(us);

  lz = __builtin_clz(ui);

  lz = __builtin_clzl(ul);

  lz = __builtin_clzll(ull);

  lz = __builtin_clz(ui128);

  lz = __builtin_clz(ubi128);

  lz = __builtin_clz(uc);

  lz = __builtin_clz(us);

  lz = __builtin_clz(ui);

  lz = __builtin_clzl(ul);

  lz = __builtin_clzll(ull);

  lz = __builtin_clz(ui128);

  lz = __builtin_clz(ubi128);
}