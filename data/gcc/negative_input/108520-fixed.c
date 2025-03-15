static void foo() {}
struct S {
  void (*f)();
};

[[gnu::nonnull(1)]] void bar(void *x) {
  struct S a[3] = {{foo}, {foo}, {foo}};
  for (struct S *i = a, *e = a + 3; i != e; i++) {
    i->f();
  }
}