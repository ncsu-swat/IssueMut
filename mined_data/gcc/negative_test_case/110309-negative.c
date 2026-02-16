void foo (int * __restrict a, int *b)
{
  for (int i = 0; i < 8; ++i)
    a[i] = b[i] + 42;
}