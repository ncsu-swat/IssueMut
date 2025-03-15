static char s_b[1];
static char s_c[1];
static int s_i[4];

char a;
char *b = s_b, *c = s_c;
int d, e, f, g, h;
int *i = s_i;

void foo(void) {
  unsigned p;
  d = i[0];
  e = i[1];
  f = i[2];
  g = i[3];
  p = d * b[0];
  p += f * c[h];
  p += e * b[h];
  p += g * c[h];
  a = (p + 8000) >> (__SIZEOF_INT__ * __CHAR_BIT__ / 2);
}