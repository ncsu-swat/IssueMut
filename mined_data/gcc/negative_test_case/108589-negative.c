int i;
__int128 j;
short s;

void foo(void) {
  j -= i;
  asm volatile ("" ::: "memory");
  int l = i - __builtin_sub_overflow_p(0, 61680, s);
  j -= __builtin_mul_overflow_p(i, l, 0);
}