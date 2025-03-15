#define GENFUN1(C)                                                             \
  __attribute__((optimize("O2"))) int foo_##C(int x) {                         \
    int cc;                                                                    \
    asm volatile("ahi %[x],42\n" : [x] "+d"(x), "=@cc"(cc));                   \
    return cc == C ? 42 : 0;                                                   \
  }

#define GENFUN2(C1, C2)                                                        \
  __attribute__((optimize("O2"))) int foo_##C1##C2(int x) {                    \
    int cc;                                                                    \
    asm volatile("ahi %[x],42\n" : [x] "+d"(x), "=@cc"(cc));                   \
    return cc == C1 || cc == C2 ? 42 : 0;                                      \
  }

#define GENFUN3(C1, C2, C3)                                                    \
  __attribute__((optimize("O2"))) int foo_##C1##C2##C3(int x) {                \
    int cc;                                                                    \
    asm volatile("ahi %[x],42\n" : [x] "+d"(x), "=@cc"(cc));                   \
    return cc == C1 || cc == C2 || cc == C3 ? 42 : 0;                          \
  }

GENFUN1(0)
GENFUN1(1)
GENFUN1(2)
GENFUN1(3)
GENFUN2(0, 1)
GENFUN2(0, 2)
GENFUN2(0, 3)
GENFUN2(1, 2)
GENFUN2(1, 3)
GENFUN2(2, 3)
GENFUN3(0, 1, 2)
GENFUN3(0, 1, 3)
GENFUN3(0, 2, 3)
GENFUN3(1, 2, 3)