int foo(unsigned bar) {
  if (bar == 0)
    return 0;
  if ((bar & (bar - 1)) != 0)
    return 0;

  if (bar == (1U << 0))
    return 1;
  if (bar == (1U << 1))
    return 2;
  if (bar == (1U << 2))
    return 3;
  if (bar == (1U << 3))
    return 4;
  if (bar == (1U << 4))
    return 8;
  if (bar == (1U << 5))
    return 13;
  if (bar == (1U << 6))
    return 21;

  return 0;
}