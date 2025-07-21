#include <riscv_vector.h>

int main() {
  unsigned int arraya[128], arrayb[128], arrayc[128];
  for (int i = 0; i < 128; i++) {
    arraya[i] = arrayb[i] + arrayc[i];
  }
  return 0;
}