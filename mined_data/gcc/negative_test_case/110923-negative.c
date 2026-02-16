int a, b, c, d;
int main() {
  for (a = 0; a < 2; a++) {
    b = 3;
    if (b > 2)
      c = 0;
    if (b > a)
      d = 0;
  }
  return 0;
}