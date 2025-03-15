struct S {
  long a, b;
};

int foo(struct S *v) {
  long tmp;
  while (1) {
    tmp = __atomic_load_n(&v->b, __ATOMIC_ACQUIRE);
    if (tmp)
      return 1;
  }
}