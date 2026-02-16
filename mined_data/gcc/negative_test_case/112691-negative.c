int __attribute__((noinline, noipa)) f1(int i) {
  char a[i + 1];
  char b[i + 2];
  b[1] = 3;
  a[0] = 5;
  return a[0] + b[1];
}

int main() {
  volatile int j;
  int x = 5;
  j = f1(x);
  return 0;
}