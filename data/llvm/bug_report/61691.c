typedef unsigned long size_t;

// Clang requires these attributes for a function to be redefined.
#define AVAILABLE_EXTERNALLY                                                   \
  extern inline __attribute__((always_inline)) __attribute__((gnu_inline))

#define AVAILABLE_EXTERNALLY_ALTERNATE                                         \
  extern inline __attribute__((__always_inline__))                             \
  __attribute__((__artificial__))

// Clang recognizes an inline builtin and renames it to prevent conflict with
// builtins.
AVAILABLE_EXTERNALLY_ALTERNATE void *memmove(void *a, const void *b, size_t c) {
  asm("# memmove.inline marker");
  return __builtin_memmove(a, b, c);
}

void *foo_alt(void *a, const void *b, size_t c) { return memmove(a, b, c); }

void bar_alt(void *a, const void *b, size_t c) {
  void *(*cpy)(void *, const void *, size_t) = c > 10 ? memmove : foo_alt;
  cpy(a, b, c);
}