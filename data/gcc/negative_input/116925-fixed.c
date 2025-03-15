typedef float V __attribute__((vector_size(16)));
V a, b, c;

void foo() { c = a < b ? b : a; }