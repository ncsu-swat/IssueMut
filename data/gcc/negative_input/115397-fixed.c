int LONG_divide_AVX512F_dimensions_0;
void npy_set_floatstatus_overflow();
void LONG_divide_AVX512F() {
  long *src = 0;
  int raise_err = 0;
  for (; LONG_divide_AVX512F_dimensions_0;
       --LONG_divide_AVX512F_dimensions_0, ++src) {
    long a = *src;
    if (a)
      raise_err = 1;
  }
  if (raise_err)
    npy_set_floatstatus_overflow();
}