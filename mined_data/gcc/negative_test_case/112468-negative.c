double foo (double x)
{
  double one = 1.;
  return __builtin_copysign (x, one);
}
double bar (double x)
{
  double minuszero = 0.;
  return __builtin_copysign (x, minuszero);
}