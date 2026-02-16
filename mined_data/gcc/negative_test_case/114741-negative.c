#pragma GCC target "+nosve"

#include <arm_neon.h>
#include <math.h>


float32_t f1(float32_t a) { return -fabsf(a); }


float64_t f2(float64_t a) { return -fabs(a); }