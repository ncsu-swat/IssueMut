void clang_analyzer_dump_int(int);

void f4(char *array) {
  char b[4] = {0};

  _Static_assert(sizeof(int) == 4, "Wrong triple for the test");

  clang_analyzer_dump_int(*(const int *)(const void *)b);
  clang_analyzer_dump_int(array[*(const int *)(const void *)b]);

  array[*(const int *)(const void *)b] = 0x10;
}