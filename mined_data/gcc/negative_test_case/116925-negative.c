typedef float V __attribute__((vector_size(16)));
V a, b, c;

void foo() {
  V temp = b;
  c = a > temp ? a : temp;
}