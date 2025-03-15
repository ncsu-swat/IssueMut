static int b;
int *a, c, *d = &c;
int main() {
  int e = 0;
  while (e < 8) {
    int *f = &b;
    int g[8];
    for (int h = 0; h < 8; h++) {
      g[h] = 0;
    }
    *f -= 1;
    *d = g[0] || a;
    e++;
  }
  return 0;
}