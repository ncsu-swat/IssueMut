struct foo {
  int x, y, z;
  struct bar {
    int count;
    int array[];
  };
};

void init(void *__attribute__((pass_dynamic_object_size(0))));

void test1(struct bar *p) { init(p->array); }

struct mux {
  int count;
  int array[];
};

struct bux {
  struct mux x;
};

void test2(struct bux *p) { init(p); }