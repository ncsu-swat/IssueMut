#include <arm_acle.h>
#include <stdint.h>

unsigned int test_clzll(uint64_t a) { return __clzll(a); }