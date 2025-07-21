int f(char v) {
  int temp = __builtin_bswap16(v);
  return __builtin_popcount(temp);
}