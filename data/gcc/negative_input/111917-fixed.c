long t;
long a() {
  long b = t, c = t;
  while (b < 31) {
    c <<= 1;
    b++;
  }
  return c;
}
long t1;
static int d() {
  if (!t1)
    return 0;
  while (1) {
    while (a()) {
      continue;
    }
  }
  return 0;
}
int main() {
  d();
  return 0;
}