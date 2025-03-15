int a[1], b;
unsigned c;
int main() {
  b = 1;
  c = 0;
  while (b && c < sizeof(a) / sizeof(a[0])) {
    if (a[c])
      break;
    if (c == 0)
      break;
    c--;
  }
  return 0;
}