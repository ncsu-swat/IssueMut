union U1 {
  int x;
  char y[16];
};

struct S1 {
  int x;
  union U1 y;
};

union U2 {
  int x;
  char y[16];
} __attribute__((__aligned__(32)));

struct S2 {
  int x;
  long long y;
  char z[8];
} __attribute__((__aligned__(32)));

union U1 global_u1 = {0};

union U1 global_u2 = {3};

union U1 global_u2_from_cast = (union U1)3;

struct S1 global_s1 = {0};

struct S1 global_s2 = {
    .x = 3,
};

struct S1 global_s3 = {.x = 3, .y = {.x = 6}};

const union U1 global_const_u1 = {4};
struct S1 global_s3_from_const_u1 = {.y = global_const_u1};

union U2 global_u3 = {0};

struct S2 global_s4 = {0};

struct S2 global_s5 = {.x = 1};

void test1() { union U1 a = {0}; }

void test2() { static union U1 a = {0}; }

void test3() { union U1 a = {3}; }

void test4() { static union U1 a = {3}; }

void test5() { struct S1 s = {0}; }

void test6() { static struct S1 s = {0}; }

void test7() {
  struct S1 s = {
      .x = 3,
  };
}

void test8() {
  static struct S1 s = {
      .x = 3,
  };
}

void test9() {
  struct S1 s = {.x = 3,
                 .y = {
                     .x = 6,
                 }};
}

void test10() {
  static struct S1 s = {.x = 3,
                        .y = {
                            .x = 6,
                        }};
}

void test11() { union U2 a = {0}; }

void test12() { static union U2 a = {0}; }

void test13() { struct S2 s = {0}; }

void test14() { static struct S2 s = {0}; }

void test15() { struct S2 s = {.x = 1}; }

void test16() { static struct S2 s = {.x = 1}; }