struct S {
  unsigned int e1 : 8;
  unsigned int e2 : 8;
  unsigned int e3 : 8;
};

unsigned int f2(struct S s) { return s.e2; }