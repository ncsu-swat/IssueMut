#include <stddef.h>
struct S {
  int a;
};
int main(void) { offsetof(struct S, a); }