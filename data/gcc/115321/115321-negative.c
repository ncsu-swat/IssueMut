unsigned foo(unsigned x) {
  __asm__ ("" : "+r" (x));
  return __builtin_bswap32(x);
}