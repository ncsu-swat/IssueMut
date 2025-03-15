#include <stdint.h>

typedef int32_t vnx4si __attribute__((vector_size(16)));

__attribute__((noipa)) void f_vnx4si(int32_t a, int32_t b, int32_t *out) {
  vnx4si v = {a, b, 0, 0};
  *(vnx4si *)out = v;
}