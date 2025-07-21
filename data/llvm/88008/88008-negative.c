struct S {
  int v;
};

struct T {
  int y;
};

void gh88008_nocrash(struct T *t) { struct S s = {.v = t->y}; }