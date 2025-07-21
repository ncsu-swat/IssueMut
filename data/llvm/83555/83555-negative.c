#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef int (*nested_func_t)(int x);

nested_func_t proc;

int c = 10;
int d = 7;

int bar(int x) { return x * 5 + c * d; };

int main() {

  proc = bar;

  c = 4;
  if ((*proc)(3) != 43)
    return 1;
  d = 5;
  if ((*proc)(4) != 40)
    return 1;

  return 0;
}