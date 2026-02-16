#if __BITINT_MAXWIDTH__ >= 639
typedef _BitInt(639) B;
#else
typedef _BitInt(63) B;
#endif

void foo(B n) { extern void bar(int(*)[(__UINT64_TYPE__)n]); }