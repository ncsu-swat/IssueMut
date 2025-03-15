#include <stdio.h>

int main() {
  _BitInt(16) bitint;
  printf("%d", __builtin_classify_type(typeof(bitint)));
  return 0;
}