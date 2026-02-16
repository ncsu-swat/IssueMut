void bar(unsigned int *__restrict b, unsigned int *__restrict d) {
  unsigned char *p = (unsigned char *)b;
  d[0] = __builtin_popcount(p[0]) + __builtin_popcount(p[1]) + __builtin_popcount(p[2]) + __builtin_popcount(p[3]);
  d[1] = __builtin_popcount(p[4]) + __builtin_popcount(p[5]) + __builtin_popcount(p[6]) + __builtin_popcount(p[7]);
  d[2] = __builtin_popcount(p[8]) + __builtin_popcount(p[9]) + __builtin_popcount(p[10]) + __builtin_popcount(p[11]);
  d[3] = __builtin_popcount(p[12]) + __builtin_popcount(p[13]) + __builtin_popcount(p[14]) + __builtin_popcount(p[15]);
}


void bar1(unsigned int *__restrict b, unsigned int *__restrict d) {
  unsigned char *p = (unsigned char *)b;
  d[0] = __builtin_popcount(p[0]) + __builtin_popcount(p[1]) + __builtin_popcount(p[2]) + __builtin_popcount(p[3]);
  d[1] = __builtin_popcount(p[4]) + __builtin_popcount(p[5]) + __builtin_popcount(p[6]) + __builtin_popcount(p[7]);
}


void bar2(unsigned long long *__restrict b, unsigned long long *__restrict d) {
  unsigned char *p = (unsigned char *)b;
  d[0] = __builtin_popcount(p[0]) + __builtin_popcount(p[1]) + __builtin_popcount(p[2]) + __builtin_popcount(p[3]) + __builtin_popcount(p[4]) + __builtin_popcount(p[5]) + __builtin_popcount(p[6]) + __builtin_popcount(p[7]);
  d[1] = __builtin_popcount(p[8]) + __builtin_popcount(p[9]) + __builtin_popcount(p[10]) + __builtin_popcount(p[11]) + __builtin_popcount(p[12]) + __builtin_popcount(p[13]) + __builtin_popcount(p[14]) + __builtin_popcount(p[15]);
}