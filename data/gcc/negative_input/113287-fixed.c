#include "tree-vect.h"

__attribute__((noipa)) void bar(unsigned long long *p) {
  __builtin_memset(p, 0, 142 * sizeof(unsigned long long));
  p[17] = 0x50000000000ULL;
}

__attribute__((noipa)) int foo(void) {
  unsigned long long r[142];
  bar(r);
  unsigned long long v = ((long long)r[0] >> 31);
  if (v + 1 > 1)
    return 1;

  // Prevent vectorization of the loop by making it more complex
  unsigned long long result = 0;
  for (unsigned long long i = 1; i <= 140; ++i) {
    result |= (r[i] != v);
    if (result)
      break;
  }
  if (result)
    return 1;

  unsigned long long w = r[141];
  if ((unsigned long long)(((long long)(w << 60)) >> 60) != v)
    return 1;
  return 0;
}

int main() {
  check_vect();

  if (foo() != 1)
    __builtin_abort();
}