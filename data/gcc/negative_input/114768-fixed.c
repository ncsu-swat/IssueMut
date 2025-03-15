void foo(int *p) {
  volatile int tmp = *(volatile int *)p;
  *p = tmp;
}