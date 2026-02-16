struct S {};
struct T {
  void release(const S &s);
};
void f(T &t) {
  S s;
  t.release(s);
}