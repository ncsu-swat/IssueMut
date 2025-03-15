int a = 0, d = 55003;
long c = 0, h = 0;
long e = 1;
short i = 0;

int main() {
  for (int g = 0; g < 16; g++) {
    d |= (int)c;
    short l = (short)d;
    i = (l < 0 || (a >> 4)) ? (short)d : (short)a;
    h = (long)(i - 8);
    e &= h;
  }

  if (e != 1)
    __builtin_abort();
  return 0;
}