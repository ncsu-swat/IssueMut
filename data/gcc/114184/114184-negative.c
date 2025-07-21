typedef unsigned char V __attribute__((vector_size(32)));
typedef unsigned char W __attribute__((vector_size(16)));

_Complex long double foo(void) {
  _Complex long double d;
  V v = {149, 136, 89, 42, 38, 240, 196, 194};
  *(V *)&d = v;
  return d;
}

long double bar(void) {
  long double d;
  W w = {149, 136, 89, 42, 38, 240, 196, 194};
  *(W *)&d = w;
  return d;
}