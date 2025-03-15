int f(char v) {
  unsigned short temp = (unsigned short)v;
  return __builtin_popcount(temp);
}