__attribute__((noipa)) int f(int a) {
  int tmp = a & 2;
  return (tmp != 1);
}
int main(void) {
  int t = f(1);
  if (!t)
    __builtin_abort();
  __builtin_printf("%d\n", t);
  return 0;
}