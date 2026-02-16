float foo(float x, float y) {
  volatile float a = x;
  volatile float b = y;
  return a + b;
}