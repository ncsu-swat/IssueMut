int test(unsigned array[8]);

int foo(char *a, char *b) {
  unsigned array[8];

  for (int i = 0; i < 8; i++) {
    array[i] = (unsigned)(a[i] - b[i]);
  }

  return test(array);
}