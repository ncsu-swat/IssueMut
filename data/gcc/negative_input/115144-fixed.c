extern void abort(void);

int foo(int x, int y, int f) {
  volatile int tem = x / y;
  if (f)
    abort();
  return tem;
}