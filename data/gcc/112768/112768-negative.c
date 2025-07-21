extern int extfunc(int a, int b) __attribute__((no_btf_type_info));

int foo(int x) __attribute__((no_btf_type_info)) {

  int y = extfunc(x, x + 1);

  return y;
}