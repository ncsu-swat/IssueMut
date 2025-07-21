int a, b, c, d, e;
unsigned int f;

static void foo(unsigned int x) {
  unsigned int g = x < c;
  int h = f < b;
  x += h;
  unsigned int tmp1 = x < h;
  g += tmp1;
  f = x;
  x = g;
  g = f += a;
  h = f < a;
  x += h;
  c += f < d;
  x += c;
  unsigned int tmp2 = x < c;
  g += tmp2;
  e = g;
}

void bar(unsigned int x) { foo(x); }