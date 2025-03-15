typedef __UINT8_TYPE__ uint8_t;

uint8_t use_pary1(int y, uint8_t x) {
  return (uint8_t)(1 + __builtin_parity((uint8_t)x));
}

uint8_t use_pary2(uint8_t x) {
  x = (uint8_t)(x + 1);
  return (uint8_t)(1 - __builtin_parity((uint8_t)x));
}