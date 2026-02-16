struct A {
  int type;
};

struct B : A {
  int value;
};

struct C : A {
  int value;
  int value2;
};

int foo(A *p) {
  if (p->type == 0)
    return static_cast<B *>(p)->value;
  return static_cast<C *>(p)->value;
}

int bar(A *p) {
  if (p->type == 0)
    return static_cast<B *>(p)->value;
  return static_cast<C *>(p)->value;
}

int zeta(A *p) {
  if (p->type == 0)
    return static_cast<B *>(p)->value;
  return static_cast<C *>(p)->value;
}