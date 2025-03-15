int foo(int j) {
  int c[1][10][1] = {0};
  c[0][1][0] = 1;
  c[0][1][0] = 0;
  return c[0][j][0];
}

int main() {
  if (foo(1) != 0)
    __builtin_abort();
  return 0;
}