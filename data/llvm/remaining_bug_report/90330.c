#include <stdatomic.h>

struct Z {
  char z[];
};

void zeroSizeArgError(struct Z *a, struct Z *b, struct Z *c) {
  __atomic_exchange(
      b, b, c, memory_order_relaxed); // expected-error {{address argument to
                                      // atomic builtin must be a pointer to a
                                      // non-zero-sized object}}
  __atomic_exchange(
      b, b, c, memory_order_acq_rel); // expected-error {{address argument to
                                      // atomic builtin must be a pointer to a
                                      // non-zero-sized object}}
  __atomic_exchange(
      b, b, c, memory_order_acquire); // expected-error {{address argument to
                                      // atomic builtin must be a pointer to a
                                      // non-zero-sized object}}
  __atomic_exchange(
      b, b, c, memory_order_consume); // expected-error {{address argument to
                                      // atomic builtin must be a pointer to a
                                      // non-zero-sized object}}
  __atomic_exchange(
      b, b, c, memory_order_release); // expected-error {{address argument to
                                      // atomic builtin must be a pointer to a
                                      // non-zero-sized object}}
  __atomic_exchange(
      b, b, c, memory_order_seq_cst); // expected-error {{address argument to
                                      // atomic builtin must be a pointer to a
                                      // non-zero-sized object}}
  __atomic_load(a, b,
                memory_order_relaxed); // expected-error {{address argument to
                                       // atomic builtin must be a pointer to a
                                       // non-zero-sized object}}
  __atomic_load(a, b,
                memory_order_acq_rel); // expected-error {{address argument to
                                       // atomic builtin must be a pointer to a
                                       // non-zero-sized object}}
  __atomic_load(a, b,
                memory_order_acquire); // expected-error {{address argument to
                                       // atomic builtin must be a pointer to a
                                       // non-zero-sized object}}
  __atomic_load(a, b,
                memory_order_consume); // expected-error {{address argument to
                                       // atomic builtin must be a pointer to a
                                       // non-zero-sized object}}
  __atomic_load(a, b,
                memory_order_release); // expected-error {{address argument to
                                       // atomic builtin must be a pointer to a
                                       // non-zero-sized object}}
  __atomic_load(a, b,
                memory_order_seq_cst); // expected-error {{address argument to
                                       // atomic builtin must be a pointer to a
                                       // non-zero-sized object}}
  __atomic_store(a, b,
                 memory_order_relaxed); // expected-error {{address argument to
                                        // atomic builtin must be a pointer to a
                                        // non-zero-sized object}}
  __atomic_store(a, b,
                 memory_order_acq_rel); // expected-error {{address argument to
                                        // atomic builtin must be a pointer to a
                                        // non-zero-sized object}}
  __atomic_store(a, b,
                 memory_order_acquire); // expected-error {{address argument to
                                        // atomic builtin must be a pointer to a
                                        // non-zero-sized object}}
  __atomic_store(a, b,
                 memory_order_consume); // expected-error {{address argument to
                                        // atomic builtin must be a pointer to a
                                        // non-zero-sized object}}
  __atomic_store(a, b,
                 memory_order_release); // expected-error {{address argument to
                                        // atomic builtin must be a pointer to a
                                        // non-zero-sized object}}
  __atomic_store(a, b,
                 memory_order_seq_cst); // expected-error {{address argument to
                                        // atomic builtin must be a pointer to a
                                        // non-zero-sized object}}
  __atomic_compare_exchange(
      a, b, c, 0, memory_order_relaxed,
      memory_order_relaxed); // expected-error {{address argument to atomic
                             // builtin must be a pointer to a non-zero-sized
                             // object}}
  __atomic_compare_exchange(
      a, b, c, 0, memory_order_acq_rel,
      memory_order_acq_rel); // expected-error {{address argument to atomic
                             // builtin must be a pointer to a non-zero-sized
                             // object}}
  __atomic_compare_exchange(
      a, b, c, 0, memory_order_acquire,
      memory_order_acquire); // expected-error {{address argument to atomic
                             // builtin must be a pointer to a non-zero-sized
                             // object}}
  __atomic_compare_exchange(
      a, b, c, 0, memory_order_consume,
      memory_order_consume); // expected-error {{address argument to atomic
                             // builtin must be a pointer to a non-zero-sized
                             // object}}
  __atomic_compare_exchange(
      a, b, c, 0, memory_order_release,
      memory_order_release); // expected-error {{address argument to atomic
                             // builtin must be a pointer to a non-zero-sized
                             // object}}
  __atomic_compare_exchange(
      a, b, c, 0, memory_order_seq_cst,
      memory_order_seq_cst); // expected-error {{address argument to atomic
                             // builtin must be a pointer to a non-zero-sized
                             // object}}
}
