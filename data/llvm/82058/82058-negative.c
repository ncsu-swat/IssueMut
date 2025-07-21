#ifdef __x86_64__
void test_builtin_popcountg(unsigned char uc, unsigned short us,
                            unsigned int ui, unsigned long ul,
                            unsigned long long ull, unsigned __int128 ui128,
                            unsigned _BitInt(128) ubi128) {
  volatile int pop;
  pop = __builtin_popcountg(uc);

  pop = __builtin_popcountg(us);

  pop = __builtin_popcountg(ui);

  pop = __builtin_popcountg(ul);

  pop = __builtin_popcountg(ull);

  pop = __builtin_popcountg(ui128);

  pop = __builtin_popcountg(ubi128);
}

#endif

typedef int int2 __attribute__((ext_vector_type(2)));

void test_builtin_popcountg(int i, double d, int2 i2) {
  __builtin_popcountg(i);
}