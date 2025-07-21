struct S {
  void *c;
  char d[16];
} a, b;

int foo(void) {
  for (unsigned int i = 0; i < sizeof(a.d); i++) {
    if (a.d[i] != b.d[i])
      return 1;
  }
  return 0;
}