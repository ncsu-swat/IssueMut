int b = 0, c = 8, d;
int e[23];
int main() {
  int *h = e;
  for (int i = 1; i < b + 21; i += 2) {
    c *= -1;
    d = h[i] ? i : 0;
  }
  __builtin_printf("%u\n", c);
}