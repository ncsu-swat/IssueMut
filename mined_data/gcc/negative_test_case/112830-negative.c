typedef __SIZE_TYPE__ size_t;

/* This version uses the same generic address space for both source and
   destination, which avoids the bug in the compiler's address space
   conversion logic. */
void copy_n_working(void *vdst, const void *vsrc, size_t n) {
  typedef struct {
    char a[n];
  } T;
  T *dst = (T *)vdst;
  const T *src = (const T *)vsrc;
  *dst = *src;
}