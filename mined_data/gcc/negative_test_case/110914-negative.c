__attribute__((noipa)) int foo(const char *s, unsigned long l) {
  volatile unsigned char r = 0;
  __builtin_memcpy((void *)&r, s, l != 0);
  return r;
}

int main() {
  const char *p = "123456";
  int a = foo(p, __builtin_strlen(p) - 5);
  int b = foo(p, __builtin_strlen(p) - 6);
  if (a != '1')
    __builtin_abort();
  if (b != 0)
    __builtin_abort();
  return 0;
}