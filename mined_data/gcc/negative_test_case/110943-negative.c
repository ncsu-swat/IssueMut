#include <riscv_vector.h>

void foo9 (void *base, void *out, size_t vl)
{
    int64_t scalar = *(int64_t*)(base + 100);
    vint64m2_t v = __riscv_vmv_s_x_i64m2 (0, 1);
    *(vint64m2_t*)out = v;
}