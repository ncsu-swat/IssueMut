struct A {};
int foo(const A &a, int i);

#include "foo.h"
int foo(const A &a, int i) { return i; }

#include "foo.h"

int main() {
  A a;
  return foo(a, 5);
}