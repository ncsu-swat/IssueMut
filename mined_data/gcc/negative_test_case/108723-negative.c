__attribute__((optimize("Os"))) __attribute__((no_unwind_tables)) void
store1z(int *array) {
  array[200] = 0;
  array[201] = 0;
  array[202] = 0;
  array[203] = 0;
}

__attribute__((optimize("Os"))) __attribute__((no_unwind_tables)) void
store2z(long long *array) {
  array[200] = 0;
  array[201] = 0;
  array[202] = 0;
  array[203] = 0;
}