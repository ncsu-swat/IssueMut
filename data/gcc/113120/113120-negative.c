#if __BITINT_MAXWIDTH__ >= 513
typedef _BitInt(513) B;
#else
typedef int B;
#endif

static inline __attribute__((__always_inline__)) void bar(B x) {
  B y = x;
  if (y != 0)
    __builtin_abort();
}

void foo(void) { bar(0); }