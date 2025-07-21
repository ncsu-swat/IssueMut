enum E { X };

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
struct __attribute__((scalar_storage_order("big-endian"))) {
  unsigned int e;
} S;
#else
struct __attribute__((scalar_storage_order("little-endian"))) {
  unsigned int e;
} S;
#endif