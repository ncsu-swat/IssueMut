struct S {
  void *c;
  char d[16];
} a, b;

int foo(void) {
  int result = 0;
  for (int i = 0; i < 16; i++) {
    if (a.d[i] != b.d[i]) {
      result = 1;
      break;
    }
  }
  return result;
}