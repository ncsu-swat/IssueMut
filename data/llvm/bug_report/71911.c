#include <stdio.h>

int main() {
  _BitInt(16) bitint;
  printf("%d", __builtin_classify_type(bitint));
  return 0;
}
