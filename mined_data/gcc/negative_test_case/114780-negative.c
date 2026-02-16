#include <stddef.h>

[[gnu::sentinel]] void foo(int, ...);
[[gnu::sentinel]] void bar(...);

void baz(nullptr_t p) {
  foo(1, 2, (void*)nullptr);
  foo(3, 4, 5, (void*)p);
  bar((void*)nullptr);
  bar((void*)p);
  foo(6, 7, 0); 
  bar(0);       
  foo(8, 9, NULL);
  bar(NULL);
}