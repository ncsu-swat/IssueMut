#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long Tal4llong __attribute__((aligned(4)));
struct S271 {
  int a;
  Tal4llong b;
};
struct S271 s271;

void check271(struct S271 arg) {
  printf("arg.b:%llx\n", arg.b);
  if (arg.b != s271.b)
    printf("Fail\n");
}

int main(void) {
  s271.b = 0x7ffffffff;
  check271(s271);
}