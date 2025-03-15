unsigned foo(unsigned x) {
  register unsigned rx = x;
  return __builtin_bswap32(rx);
}