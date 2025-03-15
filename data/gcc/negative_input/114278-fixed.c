void foo(void *p) {
  _BitInt(64) b;
  __builtin_memcpy(&b, p, sizeof(_BitInt(64)));
}

#if __BITINT_MAXWIDTH__ >= 128
void bar(void *p) {
  _BitInt(128) b;
  __builtin_memcpy(&b, p, sizeof(_BitInt(128)));
}
#endif

#if __BITINT_MAXWIDTH__ >= 256
void baz(void *p) {
  _BitInt(256) b;
  __builtin_memcpy(&b, p, sizeof(_BitInt(256)));
}
#endif