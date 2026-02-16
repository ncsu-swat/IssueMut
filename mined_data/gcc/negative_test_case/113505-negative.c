enum E **foo() __attribute__((__const__));
char a[2];
void bar(char *);

void baz(void) {
  char *s, *l;
  for (;;) {
    bar(a);
    s = a;
    enum E **const tbl = foo();
    while (tbl[*s])
      s++;
    l = s;
    *l++ = '\0';
    while (tbl[*l])
      l++;
    bar(s);
  }
}