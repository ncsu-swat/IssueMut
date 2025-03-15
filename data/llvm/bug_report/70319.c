// foo.h
struct A {};
int foo(A a, int i);

// foo.cpp
#include "foo.h"
int foo(A a, int i) { return i; }

// main.cpp
#include "foo.h"

int main() {
  A a;
  return foo(a, 5);
}