__attribute__((__cold__)) void foo(void);
void bar(void);

void baz(void) {
  asm goto("" : : : : l1, l0);
  goto l0;
l1:
  bar();
  goto l0;
l0:
  foo();
}

void qux(void) {
  asm goto("" : : : : l1, l0);
  __builtin_unreachable();
l1:
  bar();
  goto l0;
l0:
  foo();
}