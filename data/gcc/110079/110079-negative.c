int a;
__attribute__((cold)) int bar(char *);
__attribute__((hot)) int baz(char *);

void foo(void) {
l1:
  while (a)
    ;
  bar("");
  goto l2;
  asm("");
l2:
  goto l1;
}

void qux(void) {
  if (1)
    goto l1;
  bar("");
  goto l1;
l1:
  baz("");
}

void corge(void) {
  if (1)
    goto l1;
  baz("");
l2:
  return;
l1:
  bar("");
  goto l2;
}