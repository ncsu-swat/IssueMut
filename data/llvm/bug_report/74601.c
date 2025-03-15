typedef struct {
  __float128 x;
} S;

void bar(__float128 x);

void test(S x) { bar(x.x); }