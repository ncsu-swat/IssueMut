typedef unsigned long size_t;


#define AVAILABLE_EXTERNALLY                                                   \
  extern inline __attribute__((always_inline)) __attribute__((gnu_inline))

#define AVAILABLE_EXTERNALLY_ALTERNATE                                         \
  extern __attribute__((__artificial__))


AVAILABLE_EXTERNALLY_ALTERNATE void *memmove(void *a, const void *b, size_t c) {
  asm("# memmove.inline marker");
  return __builtin_memmove(a, b, c);
}

void *foo_alt(void *a, const void *b, size_t c) { return memmove(a, b, c); }

void bar_alt(void *a, const void *b, size_t c) {
  void *(*cpy)(void *, const void *, size_t) = c > 10 ? memmove : foo_alt;
  cpy(a, b, c);
}