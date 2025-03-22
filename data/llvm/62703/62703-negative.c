unsigned int test32(unsigned int x) {
  return __builtin_rotateleft32(x, 8) & 0xFF00FF00;
}

unsigned long test64(unsigned long x) {
  return __builtin_rotateleft64(x, 8) & 0xFF00FF00FF00FF00L;
}