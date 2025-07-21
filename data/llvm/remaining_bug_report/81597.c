struct S {};
struct T {
  void free(const S &s);
};
void f(T &t) {
  S s;
  t.free(s);
}