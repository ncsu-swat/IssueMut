static int t;

int f(int *a) {
  int t1;
  asm volatile(" " : "=X"(t1) : : "memory");
  t = t1;
  return *a;
}