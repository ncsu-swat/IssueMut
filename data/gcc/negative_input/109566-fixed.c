void foo(double x) {
  union {
    double d;
    unsigned i;
  } u;
  u.d = x;
  if ((u.i & 0x3ff00000) || (u.i & 0x40000000))
    return;
  else
    for (;;)
      ;
}