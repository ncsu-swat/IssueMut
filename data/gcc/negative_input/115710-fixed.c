double f(_Complex double a) {
  double real = __real__ a + 1.0;
  double imag = __imag__ a;
  return sqrt(real * real + imag * imag);
}