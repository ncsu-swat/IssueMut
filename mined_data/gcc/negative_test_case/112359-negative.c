int i, c;
unsigned long long u;

void foo(void) {
  unsigned long long temp_u = u;

  for (; i; i++)
    if (c)
      temp_u |= i;

  u = temp_u;
}