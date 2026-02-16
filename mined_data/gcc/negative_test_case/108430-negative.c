long d = 1;
static int i = 37;
static unsigned long a[22];
static unsigned short c[22];
static unsigned g[80];
static unsigned short *h = c;
static unsigned long *j = a;
int main() {
  for (unsigned char p = 0; p < 17; p += 2)
  {
    long t = h[p] ? i : j[p];
    g[p] = t;
  }
  if (g[0])
    __builtin_abort ();
}