int a, b, c, d, e;
unsigned int f;

static void foo(unsigned int x) {
  unsigned int g, h;

  g = x < c ? 1u : 0u;
  h = f < b ? 1 : 0;
  x += (unsigned int)h;
  g += (x < (unsigned int)h) ? 1u : 0u;
  f = x;
  x = g;
  f += (unsigned int)a;
  g = f;
  h = (f < (unsigned int)a) ? 1 : 0;
  x += (unsigned int)h;
  c += (f < (unsigned int)d) ? 1 : 0;
  x += (unsigned int)c;
  g += (x < (unsigned int)c) ? 1u : 0u;
  e = (int)g;
}

void bar(unsigned int x) { foo(x); }