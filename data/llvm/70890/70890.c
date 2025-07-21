// foo.h
union U {};

struct B {
  U u;
  int i;
  double d;
};

int test(B b);
// foo.cpp
#include "foo.h"

int test(B b) { return b.i; }
// main.cpp
#include "foo.h"

int main() {
  B b;
  b.i = 10;
  return test(b);
}