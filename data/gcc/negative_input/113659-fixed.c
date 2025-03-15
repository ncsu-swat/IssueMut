struct Foo {
  int *ptr;
};
int Baz(struct Foo first) {
  while (first.ptr)
    if (*first.ptr++)
      return 0;
  return 1;
}