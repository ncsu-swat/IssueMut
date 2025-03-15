int main() {
  volatile const long ONE = 1L;
  volatile long y = 0L;
  volatile long x = ((long)(ONE || (y = 1L)) % 8L);
  if (y != 0)
    __builtin_abort();
  return 0;
}