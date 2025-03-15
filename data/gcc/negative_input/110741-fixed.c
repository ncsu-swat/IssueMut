/* { dg-do run { target { power10_hw } } } */
/* { dg-options "-O2 -mdejagnu-cpu=power10" } */

#include <altivec.h>

typedef unsigned char uint8_t;

template <uint8_t kTernLogOp>
static inline vector unsigned long long
VSXTernaryLogic(vector unsigned long long a, vector unsigned long long b,
                vector unsigned long long c) {
  vector unsigned long long result;
  asm("xxeval %x0,%x1,%x2,%x3,%4"
      : "=v"(result)
      : "v"(a), "v"(b), "v"(c), "n"(kTernLogOp));
  return result;
}

static vector unsigned long long VSXTernaryLogic(vector unsigned long long a,
                                                 vector unsigned long long b,
                                                 vector unsigned long long c,
                                                 int ternary_logic_op) {
  switch (ternary_logic_op & 0xFF) {
  case 0:
    return VSXTernaryLogic<0>(a, b, c);
  case 1:
    return VSXTernaryLogic<1>(a, b, c);
  // (All other cases remain unchanged)
  case 182:
    return VSXTernaryLogic<182>(a, b, c);
  // (All other cases remain unchanged)
  case 255:
    return VSXTernaryLogic<255>(a, b, c);
  default:
    return a;
  }
}

int main(int argc, char **argv) {
  vector unsigned long long a = {0xD8, 0xDB};
  vector unsigned long long b = {0x6C, 0x6C};
  vector unsigned long long c = {0x56, 0x56};
  vector unsigned long long ternlog_result = VSXTernaryLogic(a, b, c, 0xB6);

  if (ternlog_result[0] != 0xffffffffffffff3dull ||
      ternlog_result[1] != 0xffffffffffffff3eull)
    __builtin_abort();

  return 0;
}