typedef __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;

#define SFR (*(volatile uint8_t *)(0 + __AVR_SFR_OFFSET__))
#define HISFR (*(volatile uint8_t *)(0x20 + __AVR_SFR_OFFSET__))

uint8_t cset_32bit31(uint32_t x) { return !!(x & (1UL << 31)); }

uint8_t cset_24bit23(__uint24 x) { return !!(x & (1UL << 23)); }

uint8_t cset_32bit30(uint32_t x) { return !!(x & (1UL << 30)); }

uint8_t cset_32bit30_not(uint32_t x) { return !(x & (1UL << 30)); }

uint8_t cset_32bit31_not(uint32_t x) { return !(x & (1UL << 31)); }

uint8_t cset_sfr_7(uint32_t x) { return !!(SFR & (1 << 7)); }

uint8_t cset_sfr_7not(void) { return !(SFR & (1 << 7)); }

uint8_t cset_sfr_5(void) { return !!(SFR & (1 << 5)); }

uint8_t cset_sfr_5not(void) { return !(SFR & (1 << 5)); }

char zz;

void set0_sfr_5_1(void) {
  if (SFR & (1 << 5))
    zz = 0;
}

void set0_sfr_5_0(void) {
  if (!(SFR & (1 << 5)))
    zz = 0;
}

void set0_sfr_7_1(void) {
  if (SFR & (1 << 7))
    zz = 0;
}

void set0_sfr_7_0(void) {
  if (!(SFR & (1 << 7)))
    zz = 0;
}

void set0_sfr_0_1(void) {
  if (SFR & 1)
    zz = 0;
}

void set0_sfr_0_0(void) {
  if (!(SFR & 1))
    zz = 0;
}

uint8_t cset_hisfr_7(uint32_t x) { return !!(HISFR & (1 << 7)); }

uint8_t cset_hisfr_7not(void) { return !(HISFR & (1 << 7)); }

uint8_t cset_hisfr_5(void) { return !!(HISFR & (1 << 5)); }

uint8_t cset_hisfr_5not(void) { return !(HISFR & (1 << 5)); }

void set0_hisfr_5_1(void) {
  if (HISFR & (1 << 5))
    zz = 0;
}

void set0_hisfr_5_0(void) {
  if (!(HISFR & (1 << 5)))
    zz = 0;
}

void set0_hisfr_7_1(void) {
  if (HISFR & (1 << 7))
    zz = 0;
}

void set0_hisfr_7_0(void) {
  if (!(HISFR & (1 << 7)))
    zz = 0;
}

void set0_hisfr_0_1(void) {
  if (HISFR & 1)
    zz = 0;
}

void set0_hisfr_0_0(void) {
  if (!(HISFR & 1))
    zz = 0;
}