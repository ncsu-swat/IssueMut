extern int a(void);

extern int b(void);

static int h0(void);

void s(void) {
  static int h0(void);
  extern int h2(void);
}

extern int i(void);
static int j(void);

void bar(void) { extern int i(void); }

void foo(void) { static int j(void); }

void x(void) {
  int i(void);
  int j;
  { static int j(void); }
}