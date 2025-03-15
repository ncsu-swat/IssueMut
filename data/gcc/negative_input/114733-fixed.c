long b = 1;
signed char c;
int d[25];

int main() {
  volatile long tmp = b;
  for (signed char g = 0; g < 8; g += 1)
    for (short h = 0; h < 25; h += 2) {
      tmp *= -1;
      c ^= d[h];
    }
  b = tmp;
  __builtin_printf("%ld\n", b);
  return 0;
}