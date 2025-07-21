typedef __attribute__((__vector_size__(16))) _Float16 F;
typedef __attribute__((__vector_size__(32))) int V;
F f;

void foo() {
  V v = {3307};
  f += __builtin_convertvector(v, F);
}