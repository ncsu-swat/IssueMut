long x = -0x7fffffff - 1;
int main(void) {
  volatile long y = x % (-0xf - 1);
  if (-0x7fffffff - 1 + y == x == 0)
    __builtin_abort();
  return 0;
}