#define D 1

extern void bar(void);

void foo(int a, int b) {
  if (a && D)
    bar();
  if (b && D)
    bar();
}