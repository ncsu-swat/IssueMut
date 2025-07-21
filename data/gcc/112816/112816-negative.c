#define N 2
struct S {
  float x[N];
};
struct T {
  int x[N];
};

struct T foo(struct S x) {
  struct T res;
  for (int i = 0; i < N; ++i)
    res.x[i] = (x.x[i] < 0.0f) ? -1 : 0;
  return res;
}