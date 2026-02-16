#include <stdatomic.h>

int t0(int *p, int x) {
  if (x > 100)
    x = atomic_load_explicit(p, memory_order_relaxed);
  return x + 1;
}

long long t1(long long *p, int x) {
  if (x > 100)
    x = atomic_load_explicit(p, memory_order_relaxed);
  return x + 1;
}

void t2(int *p, int x) {
  if (x > 100)
    atomic_store_explicit(p, x, memory_order_relaxed);
}

void t3(long long *p, int x) {
  if (x > 100)
    (void)atomic_load_explicit(p, memory_order_relaxed);
}