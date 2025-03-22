#include <err.h>

extern int ttyname_r(int, char *, int);

int test(void) __attribute__((no_stack_protector));

int test(void) {
  char name[10];

  if (ttyname_r(0, name, 10))
    err(1, "capsicum");

  return 0;
}