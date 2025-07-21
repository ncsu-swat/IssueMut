void test_builtin_ctzg(unsigned char uc, unsigned short us, unsigned int ui,
                       unsigned long ul, unsigned long long ull,
                       unsigned __int128 ui128, unsigned _BitInt(128) ubi128,
                       signed char sc, short s, int i) {
  volatile int tz;
  tz = __builtin_ctz(uc);
  
  
  
  
  tz = __builtin_ctz(us);
  
  
  
  
  tz = __builtin_ctz(ui);
  
  
  
  tz = __builtin_ctzl(ul);
  
  
  
  
  tz = __builtin_ctzll(ull);
  
  
  
  
  tz = __builtin_ctz(ui128);
  
  
  
  
  tz = __builtin_ctz(ubi128);
  
  
  
  
  tz = uc == 0 ? sc : __builtin_ctz(uc);
  
  
  
  
  
  
  
  
  tz = us == 0 ? uc : __builtin_ctz(us);
  
  
  
  
  
  
  
  
  tz = ui == 0 ? s : __builtin_ctz(ui);
  
  
  
  
  
  
  
  tz = ul == 0 ? us : __builtin_ctzl(ul);
  
  
  
  
  
  
  
  
  tz = ull == 0 ? i : __builtin_ctzll(ull);
  
  
  
  
  
  
  
  tz = ui128 == 0 ? i : __builtin_ctz(ui128);
  
  
  
  
  
  
  
  tz = ubi128 == 0 ? i : __builtin_ctz(ubi128);
  
  
  
  
  
  
  
  
}