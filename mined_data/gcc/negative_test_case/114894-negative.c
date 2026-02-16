int fmul1(int a, int b) {
  int c = a * b;
  return c;
}

int fand1(int a, int b) {
  int c = a & b;
  return c;
}

void g(int);

int fdiv1(int a, int b) {
  int d = b | 1;
  g(d);
  int c = a / d;
  return c;
}