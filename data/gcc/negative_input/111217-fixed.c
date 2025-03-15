static inline _Bool nand(_Bool a, _Bool b) {
  _Bool t = 0;
  if (a) {
    if (b) {
      t = 1;
    }
  }
  return !t;
}

_Bool f(int a, int b) { return nand(nand(b, nand(a, a)), nand(a, nand(b, b))); }