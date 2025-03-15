void foo(int n) {
  char c[n];
  c[0] = '1';
  c[1] = '\0';
  __builtin_printf(c);
}