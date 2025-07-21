#include <stddef.h>
int main(void) {
  offsetof(
      struct { int a; }, a);
}