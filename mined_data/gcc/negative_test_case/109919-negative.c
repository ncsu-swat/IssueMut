int a;
int main() {
  int b = 1;
  short c = 0;
  while (a) {
    c = b && ((a || a) & (a * c));
  }
  return 0;
}