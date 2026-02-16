char *test;
char *copy_test() {
  char *test2 = __builtin_malloc(1000);
  __builtin_memcpy(test2, test, 1000);
  return test2;
}