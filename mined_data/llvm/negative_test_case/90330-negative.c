#include <stdatomic.h>

struct Z {
  char z[1];
};

void zeroSizeArgError(struct Z *a, struct Z *b, struct Z *c) {
  __atomic_exchange(b, b, c, memory_order_relaxed);
  __atomic_exchange(b, b, c, memory_order_acq_rel);
  __atomic_exchange(b, b, c, memory_order_acquire);
  __atomic_exchange(b, b, c, memory_order_consume);
  __atomic_exchange(b, b, c, memory_order_release);
  __atomic_exchange(b, b, c, memory_order_seq_cst);
  __atomic_load(a, b, memory_order_relaxed);
  __atomic_load(a, b, memory_order_acq_rel);
  __atomic_load(a, b, memory_order_acquire);
  __atomic_load(a, b, memory_order_consume);
  __atomic_load(a, b, memory_order_release);
  __atomic_load(a, b, memory_order_seq_cst);
  __atomic_store(a, b, memory_order_relaxed);
  __atomic_store(a, b, memory_order_acq_rel);
  __atomic_store(a, b, memory_order_acquire);
  __atomic_store(a, b, memory_order_consume);
  __atomic_store(a, b, memory_order_release);
  __atomic_store(a, b, memory_order_seq_cst);
  __atomic_compare_exchange(a, b, c, 0, memory_order_relaxed,
                            memory_order_relaxed);
  __atomic_compare_exchange(a, b, c, 0, memory_order_acq_rel,
                            memory_order_acq_rel);
  __atomic_compare_exchange(a, b, c, 0, memory_order_acquire,
                            memory_order_acquire);
  __atomic_compare_exchange(a, b, c, 0, memory_order_consume,
                            memory_order_consume);
  __atomic_compare_exchange(a, b, c, 0, memory_order_release,
                            memory_order_release);
  __atomic_compare_exchange(a, b, c, 0, memory_order_seq_cst,
                            memory_order_seq_cst);
}