extern void bar(void);

void foo(int a, int b) {
  if (a && 1)
    bar();
  if (b && 1)
    bar();
}