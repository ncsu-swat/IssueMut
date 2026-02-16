void
foo (unsigned long long *a)
{
  register long d asm ("r0") = 0x24;
  long long n;
  asm ("mr %0, %1" : "=r"(n) : "r"(d));
  *a++ = n;
}