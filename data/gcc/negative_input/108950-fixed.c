int m;
short int n;

__attribute__((simd)) int foo(void) {
  int temp = (int)n;
  m += temp;
  m += temp;
}