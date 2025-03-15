#if __BITINT_MAXWIDTH__ >= 128
typedef unsigned _BitInt(128) B;
#else
typedef unsigned int B;
#endif

static inline __attribute__((__always_inline__)) void bar(B x) {
  B y = (B)x;
  if (y)
    __builtin_abort();
}

void foo(void) { bar((B)0); }