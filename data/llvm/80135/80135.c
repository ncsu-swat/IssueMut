int test_left(unsigned _BitInt(17) x) {
  return x << 3uwb; // Shift exponent is OK (3 < 17)
}

int test_right(unsigned _BitInt(4) x) {
  return x >> 16uwb; // Shift exponent is NOK (16 >= 4)
}