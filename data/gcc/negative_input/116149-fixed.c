long a = 0;
short b[60000] = {0};
short c[20] = {0};
int main() {
  const int max_size = 20;
  for (short d = 0; d < max_size; d += 3) {
    if (d >= 0 && d < max_size) {
      c[d] = 0;
      for (int e = 0; e < max_size; e += 2) {
        for (int f = 1; f < max_size; f += 2) {
          if ((f + e) < 60000) {
            a += (unsigned)b[f + e];
          }
        }
      }
    }
  }
  if (a != 0)
    __builtin_abort();
  return 0;
}