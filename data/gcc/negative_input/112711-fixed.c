typedef int i32;
typedef unsigned int u32;

static inline void write_i32(void *memory, i32 value) {

  u32 u_value = value;
  value = __builtin_bswap32(u_value);

  __builtin_memcpy(memory, &value, sizeof(value));
}

__attribute__((noipa)) static void bug(void) {
#define assert_eq(lhs, rhs)                                                    \
  if (lhs != rhs)                                                              \
  __builtin_trap()

  unsigned char data[5];
  write_i32(data, -1362446643);
  assert_eq(data[0], 0xAE);
  assert_eq(data[1], 0xCA);
  write_i32(data + 1, -1362446643);
  assert_eq(data[1], 0xAE);
}

int main() {
  bug();
  return 0;
}