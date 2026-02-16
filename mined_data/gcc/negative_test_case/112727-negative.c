#ifndef __cplusplus
#define bool _Bool
#endif

struct S {
  bool s[8];
};

void foo(const struct S *x) {
  unsigned n = 0;
  for (unsigned j = 0; j < 8; j++)
    n |= (!x->s[j]) << (16 + j);
}