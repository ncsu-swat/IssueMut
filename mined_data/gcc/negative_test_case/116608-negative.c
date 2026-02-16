extern void abort(void);

#ifndef STATIC
#define STATIC
#endif

#define N 16

double cb[N] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45};
double ca[N];

STATIC void __attribute__((noinline)) sse2_test(void) {
  int i;

  for (i = 0; i < N; i++) {
    ca[i] = cb[i];
  }

  
  for (i = 0; i < N; i++) {
    asm volatile ("" ::: "memory");
    if (ca[i] != cb[i])
      abort();
  }
}