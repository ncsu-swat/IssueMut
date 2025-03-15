typedef unsigned long long BITBOARD;
BITBOARD KingPressureMask1[64], KingSafetyMask1[64];

void __attribute__((noinline)) foo() {
  int i;

  // Force alignment to avoid peeling
  __attribute__((aligned(64))) BITBOARD temp[64];

  for (i = 0; i < 64; i++) {
    if ((i & 7) == 0) {
      temp[i] = KingSafetyMask1[i + 1];
    } else if ((i & 7) == 7) {
      temp[i] = KingSafetyMask1[i - 1];
    } else {
      temp[i] = KingSafetyMask1[i];
    }
  }

  // Copy back results
  for (i = 0; i < 64; i++) {
    KingPressureMask1[i] = temp[i];
  }
}

BITBOARD verify[64] = {1,  1,  2,  3,  4,  5,  6,  6,  9,  9,  10, 11, 12,
                       13, 14, 14, 17, 17, 18, 19, 20, 21, 22, 22, 25, 25,
                       26, 27, 28, 29, 30, 30, 33, 33, 34, 35, 36, 37, 38,
                       38, 41, 41, 42, 43, 44, 45, 46, 46, 49, 49, 50, 51,
                       52, 53, 54, 54, 57, 57, 58, 59, 60, 61, 62, 62};

int main() {
  for (int i = 0; i < 64; ++i)
    KingSafetyMask1[i] = i;
  foo();
  for (int i = 0; i < 64; ++i)
    if (KingPressureMask1[i] != verify[i])
      __builtin_abort();
  return 0;
}