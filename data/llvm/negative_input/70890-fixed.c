union U {
  int dummy;
};

struct B {
  U u;
  int i;
  double d;
};

int test(B b);

#include "foo.h"

int test(B b) { return b.i; }

#include "foo.h"

int main() {
  B b;
  b.i = 10;
  return test(b);
}