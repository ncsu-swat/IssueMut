char arr[4];
long x;

void _S_copy(long __n) {
  __builtin_memcpy(&arr[0], &arr[3],
                   __n); /* { dg-prune-output "-Wanalyzer-out-of-bounds" } */
  /* This only warns on some targets; the purpose of the test is to verify that
     we don't ICE.  */
}

void _M_construct() {
  x = &arr[2] - &arr[1];
  unsigned long __dnew = x;
  if (__dnew > 1)
    _S_copy(&arr[2] - &arr[1]);
}