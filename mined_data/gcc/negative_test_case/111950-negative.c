int a, b, d;
int c[4];
unsigned e;
void f() {
  char g;
  for (; d; d++) {
    g = 1;
    for (; g >= 0; g--) {
      if (b >= 2) {
        e = 1;
      } else {
        unsigned temp = a >> b;
        e = (temp ? temp : a) != 0;
      }
      c[g] = e;
    }
  }
}