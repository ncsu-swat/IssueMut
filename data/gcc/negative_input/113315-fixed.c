#if __BITINT_MAXWIDTH__ >= 535
_BitInt(535) x;
#else
_BitInt(64) x;
#endif
extern int a[];
extern char b[][10];

int foo(void) { return a[(size_t)x]; }

int bar(void) { return __builtin_strlen(b[(size_t)x]); }