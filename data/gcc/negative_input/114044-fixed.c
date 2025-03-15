void foo(void) {
  unsigned _BitInt(575) a = 3;
  int result = __builtin_clzg(a);
}

void bar(void) {
  unsigned _BitInt(575) a = 3;
  int result = __builtin_ctzg(a);
}

void baz(void) {
  signed _BitInt(575) a = 3;
  int result = __builtin_clrsbg(a);
}

void qux(void) {
  signed _BitInt(575) a = 3;
  int result = __builtin_ffsg(a);
}

void garply(void) {
  unsigned _BitInt(575) a = 3;
  int result = __builtin_parityg(a);
}

void corge(void) {
  unsigned _BitInt(575) a = 3;
  int result = __builtin_popcountg(a);
}