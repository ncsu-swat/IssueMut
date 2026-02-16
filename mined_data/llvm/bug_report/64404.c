#include <riscv_vector.h>

typedef vint64m1_t __attribute__((riscv_rvv_vector_bits(128))) vint64m1_128_t;

int main() {
  vint64m1_t a;
  vint64m1_128_t b;
  vint64m1_t c = __riscv_vand(a, 0, 0);
  vint64m1_t d = __riscv_vand(b, 0, 0);
}