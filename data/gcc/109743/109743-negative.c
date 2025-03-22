#include "riscv_vector.h"

void f(int32_t *a, int32_t *b, int n) {
  if (n <= 0)
    return;
  int i = n;
  size_t vl = __riscv_vsetvl_e32m1(i);
  do {
    vint32m1_t v = __riscv_vle32_v_i32m1(a, vl);
    __riscv_vse32_v_i32m1(b, v, vl);

    if (i <= 0)
      break;
    i--;
    if (i < vl)
      vl = __riscv_vsetvl_e32m1(i);
  } while (1);
}