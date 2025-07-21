int __GIMPLE(ssa) foo(int j) {
  int c[1][10][1];
  int _1;
  int * _2;

  __BB(2) : c[0][1][0] = 1;
  c[0][1] = _Literal(int[1]){};
  _2 = &c[0][j_2(D)][0];
  _1 = *_2;
  return _1;
}

int main() {
  if (foo(1) != 0)
    __builtin_abort();
  return 0;
}