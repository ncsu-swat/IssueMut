struct variable {
  int a;
  int b;
  int length;
  short array[] __attribute__((counted_by(length)));
};

struct bucket {
  int a;
  struct variable growable;
  int b;
};

struct bucket2 {
  int a;
  struct variable growable;
};

void init(void *__attribute__((pass_dynamic_object_size(0))));

void test1(struct bucket *foo) { init(foo->growable.array); }

void test2(struct bucket2 *foo) { init(foo->growable.array); }