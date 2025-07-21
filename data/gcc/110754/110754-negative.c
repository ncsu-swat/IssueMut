int foo(int x) {
  volatile int a = x;
  [[gnu::assume(x == 0)]];
  return x;
}