void move1(void *s1, void *s2) { __builtin_memcpy(s1, s2, 16); }

void move2(void *s1) { __builtin_memcpy(s1, "0123456789012345", 16); }

int compare(const void *s1, const void *s2) {
  return __builtin_memcmp(s1, s2, 16) == 0;
}