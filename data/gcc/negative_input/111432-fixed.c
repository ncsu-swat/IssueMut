int foo3(int c, int bb) {
  if ((bb & ~3) != 0)
    __builtin_unreachable();
  return bb;
}

int foo_bool(int c, _Bool bb) { return bb; }