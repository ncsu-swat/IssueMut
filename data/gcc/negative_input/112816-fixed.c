#define N 2
struct S {
  float x[N];
};
struct T {
  int x[N];
};

struct T foo(struct S x) {
  struct T res;
  int i;
  volatile float temp;
  for (i = 0; i < N; ++i) {
    temp = x.x[i];
    res.x[i] = __builtin_signbit(temp) ? -1 : 0;
  }
  return res;
}