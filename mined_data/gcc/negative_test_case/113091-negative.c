int test(unsigned array[8]);

int foo(char *a, char *b) {
  unsigned array[8];

  array[0] = ((int)a[0] - (int)b[0]);
  array[1] = ((int)a[1] - (int)b[1]);
  array[2] = ((int)a[2] - (int)b[2]);
  array[3] = ((int)a[3] - (int)b[3]);
  array[4] = ((int)a[4] - (int)b[4]);
  array[5] = ((int)a[5] - (int)b[5]);
  array[6] = ((int)a[6] - (int)b[6]);
  array[7] = ((int)a[7] - (int)b[7]);

  return test(array);
}