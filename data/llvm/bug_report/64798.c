float fast_div(float x, float y) {
#pragma clang fp reciprocal(on)
  return x / y;
}