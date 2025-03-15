#include <stdint.h>

struct T {
  int32_t a;
};

void bar(struct T t) {}

void foo(void) {
  struct T t;
  bar(t);
}