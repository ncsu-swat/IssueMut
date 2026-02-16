#if __BITINT_MAXWIDTH__ > 128
struct S1 {
  _BitInt(17) A;
  _BitInt(129) B;
};

int foo(int a) {
  struct S1 A = {1, 170};
  struct S1 B = {1, a};
  return (int)A.B + (int)B.B;
}

struct S2 {
  _BitInt(256) A;
  int B;
};

_BitInt(256) bar() {
  struct S2 A = {1, 10000};
  return A.A;
}

void TakesVarargs(int i, ...) {
  __builtin_va_list args;
  __builtin_va_start(args, i);
  _BitInt(160) A = __builtin_va_arg(args, _BitInt(160));
}

_BitInt(129) * f1(_BitInt(129) * p) { return p + 1; }

char *f2(char *p) { return p + sizeof(_BitInt(129)); }

auto BigGlob = (_BitInt(256)) - 1;

_BitInt(256) foobar() {
  _BitInt(256) A = BigGlob + 1;
  return A;
}

void f() { static _BitInt(130) p = {10000}; }

struct S3 {
  _BitInt(136) A : 129;
};

void bitField() {
  struct S3 s = {1};
  struct {
    _BitInt(136) A : 48;
    int a;
  } s1 = {s.A};
  s1.A = 36;
}

#endif