static int c, d, e, f;
static short g;
static int *h = &c;
void foo(void);
short(a)();
static unsigned b(unsigned char j, int l) { return j > l ? j : j << l; }
static int *i();
static void k(int j, unsigned char l) {
  i();
  g = f;
  f = g;
  for (; g;) {
    int m = 0;
    d = a();
    for (; d;) {
      if (l)
        if (!(j >= -639457069 && j <= -639457069))
          if (!m)
            foo();
      m = !(10 != (l ^ b(j, 6))) & (0 > e);
    }
  }
}
static int *i() {
  for (; e; e = a(e, 6))
    ;
  return h;
}
int main() { k(c, c); }