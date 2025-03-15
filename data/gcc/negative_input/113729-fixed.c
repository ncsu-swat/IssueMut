#include <stdint.h>

#define F(TYPE1, TYPE2, OP_NAME, OP)                                           \
  TYPE1                                                                        \
  __attribute__((noipa)) f_##OP_NAME##_##TYPE2##_##TYPE1(unsigned TYPE2 b) {   \
    unsigned TYPE2 result = 200 OP b;                                          \
    return (TYPE1)result;                                                      \
  }                                                                            \
  TYPE1                                                                        \
  __attribute__((noipa))                                                       \
  f1_##OP_NAME##_##TYPE2##_##TYPE1(unsigned TYPE2 a, unsigned TYPE2 b) {       \
    unsigned TYPE2 result = a OP b;                                            \
    return (TYPE1)result;                                                      \
  }

F(short, char, add, +)
F(int, char, add, +)
F(int64_t, char, add, +)
F(int, short, add, +)
F(int64_t, short, add, +)

F(short, char, sub, -)
F(int, char, sub, -)
F(int64_t, char, sub, -)
F(int, short, sub, -)
F(int64_t, short, sub, -)

#define F1(TYPE1, TYPE2, OP_NAME, OP)                                          \
  TYPE1                                                                        \
  __attribute__((noipa)) f3_##OP_NAME##_##TYPE2##_##TYPE1(unsigned TYPE2 *a) { \
    unsigned TYPE2 b = OP * a;                                                 \
    return (TYPE1)b;                                                           \
  }

F1(short, char, neg, -)
F1(int, char, neg, -)
F1(int64_t, char, neg, -)
F1(int, short, neg, -)
F1(int64_t, short, neg, -)

F1(short, char, not, ~)
F1(int, char, not, ~)
F1(int64_t, char, not, ~)
F1(int, short, not, ~)
F1(int64_t, short, not, ~)

F(short, char, and, &)
F(int, char, and, &)
F(int64_t, char, and, &)
F(int, short, and, &)
F(int64_t, short, and, &)

F(short, char, or, |)
F(int, char, or, |)
F(int64_t, char, or, |)
F(int, short, or, |)
F(int64_t, short, or, |)

F(short, char, xor, ^)
F(int, char, xor, ^)
F(int64_t, char, xor, ^)
F(int, short, xor, ^)
F(int64_t, short, xor, ^)

#define F2(TYPE1, TYPE2, OP_NAME, OP, IMM)                                     \
  TYPE1                                                                        \
  __attribute__((noipa)) f2_##OP_NAME##_##TYPE1##_##TYPE2(TYPE2 a) {           \
    unsigned TYPE2 b = a OP IMM;                                               \
    return (TYPE1)b;                                                           \
  }

F2(short, char, shl, <<, 7)
F2(int, char, shl, <<, 6)
F2(int64_t, char, shl, <<, 7)
F2(int, short, shl, <<, 6)
F2(int64_t, short, shl, <<, 3)

F2(short, char, sar, >>, 7)
F2(int, char, sar, >>, 6)
F2(int64_t, char, sar, >>, 7)
F2(int, short, sar, >>, 6)
F2(int64_t, short, sar, >>, 3)

#define F3(TYPE1, TYPE2, OP_NAME, OP, IMM)                                     \
  TYPE1                                                                        \
  __attribute__((noipa)) f3_##OP_NAME##_##TYPE1##_##TYPE2(TYPE2 a) {           \
    TYPE2 b = a OP IMM;                                                        \
    return (TYPE1)b;                                                           \
  }

F3(short, uint8_t, shr, >>, 7)
F3(int, uint8_t, shr, >>, 6)
F3(int64_t, uint8_t, shr, >>, 7)
F3(int, uint16_t, shr, >>, 6)
F3(int64_t, uint16_t, shr, >>, 3)

#define F4(TYPE1, TYPE2, OP_NAME, OP1, OP2, IMM1)                              \
  TYPE1                                                                        \
  __attribute__((noipa))                                                       \
  foo4_##OP_NAME##_##TYPE1##_##TYPE2(unsigned TYPE2 a) {                       \
    unsigned TYPE2 b = (a OP1 IMM1 | a OP2(8 * sizeof(TYPE2) - IMM1));         \
    return (TYPE1)b;                                                           \
  }

F4(short, char, ror, >>, <<, 1)
F4(int, char, ror, >>, <<, 1)
F4(long, char, ror, >>, <<, 1)
F4(int, short, ror, >>, <<, 1)
F4(long, short, ror, >>, <<, 1)

F4(short, char, rol, <<, >>, 1)
F4(int, char, rol, <<, >>, 1)
F4(long, char, rol, <<, >>, 1)
F4(int, short, rol, <<, >>, 1)
F4(long, short, rol, <<, >>, 1)