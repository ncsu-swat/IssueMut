#if 0
#define FOO(x) x
#else
#define FOO(x) foo_##x
#endif

int foo(int a, int b, int foo_b) { return (a && FOO(b)); }
