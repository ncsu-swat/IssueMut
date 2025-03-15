int a = 3, d, e;
int *volatile b = &a;
char c;
short f;
const int **g;
static long h(int **volatile i, int **volatile j) {
  const int *k[46];
  const int **volatile l = &k[5];
  *j = &e;
  g = l;
  for (; d; d = d + 1)
    ;
  **i = 0;
  return f;
}
int main() {
  int *volatile m = &a;
  h(&m, &m);
  c = *b;
  if (c != 3)
    __builtin_abort();
  return 0;
}