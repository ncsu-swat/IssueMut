int rx, in;

int main(void) {
  enum { tj = 3 };
  int as[3];
  static int l4;

  while (l4 < 1) {
    for (rx = 0; rx < 3; ++rx) {
      for (in = 0; in < 3; ++in)
        as[in] = 1;
      as[rx] = 0;
    }
    ++l4;
  }

  if (as[2] != 0)
    __builtin_abort();
}