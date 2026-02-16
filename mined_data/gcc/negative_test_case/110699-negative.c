typedef __attribute__((__vector_size__(64))) int T;

void f(void) {
  extern char a[64], b[64]; 
  void *p = a;
  T q = *(T *)&b[0];
}

void g() { extern char b[];  }