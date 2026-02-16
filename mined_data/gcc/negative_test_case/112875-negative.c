// Bug-free input example
long a, f;
int b, c, d, g, h, i, j;
char e;
void k(long, int l, char t) {
  char m = b, n = g, o = 0;
  int p, q, r = h;
  long s = g;
  if (f) {
    // The cast to float is removed, making this integer arithmetic.
    q = t + 16777217;
    o = ~0;
  }
  if (e) {
    d = g + a;
    if (d % (a % l)) {
      p = d;
      n = b;
    }
    if (l) {
      i = b;
      r = a;
      p = h;
    }
    if (s)
      s = q;
    c = f;
    e += t;
    a = p;
  }
  j = r % n;
  s += g / 0xc000000000000000 + !o;
}