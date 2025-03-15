enum E **foo() __attribute__((__const__));
char a[2];
void bar(char *);

void baz(void) {
  char *s, *l;
  for (;;) {
    bar(a);
    s = a;
    enum E **ptr;
    while (1) {
      ptr = foo();
      if (!ptr[*s])
        break;
      s++;
    }
    l = s;
    *l++ = '\0';
    while (1) {
      ptr = foo();
      if (!ptr[*l])
        break;
      l++;
    }
    bar(s);
  }
}