#pragma GCC target("cpu=power10,pcrel")
int x(void) __attribute__((noipa));
int y(void) __attribute__((noipa));
int xx(void) __attribute__((noipa));

int x(void) { return 1; }

int y(void) { return 2; }

int sib_call(void) { return x(); }

#pragma GCC target("cpu=power9,no-pcrel")
int normal_call(void) { return y(); }

int xx(void) { return 1; }

extern int yy(void);

#pragma GCC target("cpu=power10,pcrel")
int notoc_sibcall(void) { return xx(); }

int extern_sibcall(void) { return yy(); }