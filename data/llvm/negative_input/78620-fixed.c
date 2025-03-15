void test_d0() {
  register int a asm("d0");
  asm("" ::"r"(a));
}

void test_d1() {
  register int a asm("d1");
  asm("" ::"r"(a));
}

void test_d2() {
  register int a asm("d2");
  asm("" ::"r"(a));
}

void test_d3() {
  register int a asm("d3");
  asm("" ::"r"(a));
}

void test_d4() {
  register int a asm("d4");
  asm("" ::"r"(a));
}

void test_d5() {
  register int a asm("d5");
  asm("" ::"r"(a));
}

void test_d6() {
  register int a asm("d6");
  asm("" ::"r"(a));
}

void test_d7() {
  register int a asm("d7");
  asm("" ::"r"(a));
}

void test_a0() {
  register int a asm("a0");
  asm("" ::"r"(a));
}

void test_a1() {
  register int a asm("a1");
  asm("" ::"r"(a));
}

void test_a2() {
  register int a asm("a2");
  asm("" ::"r"(a));
}

void test_a3() {
  register int a asm("a3");
  asm("" ::"r"(a));
}

void test_a4() {
  register int a asm("a4");
  asm("" ::"r"(a));
}

void test_a5() {
  register int a asm("a5");
  register int b asm("bp");
  asm("" ::"r"(a));
  asm("" ::"r"(b));
}

void test_a6() {
  register int a asm("a6");
  register int b asm("fp");
  asm("" ::"r"(a));
  asm("" ::"r"(b));
}

void test_sp() {
  register int a asm("a7");
  register int b asm("usp");
  register int c asm("ssp");
  register int d asm("isp");
  register int e asm("a7");
  asm("" ::"r"(a));
  asm("" ::"r"(b));
  asm("" ::"r"(c));
  asm("" ::"r"(d));
  asm("" ::"r"(e));
}

void test_pc() {
  register int a asm("pc");
  asm("" ::"r"(a));
}