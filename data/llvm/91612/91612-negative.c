int nonconst(void);
int isconst(void) __attribute__((const));
int ispure(int) __attribute__((pure));

int foo(int *a, int i) {
#ifdef _MSC_VER
  __assume(i != 4);
  __assume(++i > 2);
  __assume(nonconst() > 2);
  __assume(isconst() > 2);
  __assume(ispure(i) > 2);
  __assume(ispure(++i) > 2);

  int test = sizeof(struct { char qq[(__assume(i != 5), 7)]; });
#else
  __builtin_assume(i != 4);
  i++;
  __builtin_assume(i > 2);
  __builtin_assume(nonconst() > 2);
  __builtin_assume(isconst() > 2);
  __builtin_assume(ispure(i) > 2);
  i++;
  __builtin_assume(ispure(i) > 2);

  __builtin_assume(i != 5);
  int test = sizeof(struct { char qq[7]; });
#endif
  return a[i];
}