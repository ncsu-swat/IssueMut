#if !__has_attribute(counted_by)
#error "has attribute broken"
#endif

#define __counted_by(member)

#ifdef COUNTED_BY
#define __counted_by(member)
#else
#define __counted_by(member)
#endif

#define DECLARE_FLEX_ARRAY(TYPE, NAME)                                         \
  struct {                                                                     \
    struct {                                                                   \
    } __empty_##NAME;                                                          \
    TYPE NAME[];                                                               \
  }

#define DECLARE_BOUNDED_FLEX_ARRAY(COUNT_TYPE, COUNT, TYPE, NAME)              \
  struct {                                                                     \
    COUNT_TYPE COUNT;                                                          \
    TYPE NAME[] __counted_by(COUNT);                                           \
  }

#define DECLARE_FLEX_ARRAY_COUNTED_BY(TYPE, NAME, COUNTED_BY)                  \
  struct {                                                                     \
    struct {                                                                   \
    } __empty_##NAME;                                                          \
    TYPE NAME[] __counted_by(COUNTED_BY);                                      \
  }

typedef long unsigned int size_t;

struct annotated {
  unsigned long flags;
  int count;
  int array[] __counted_by(count);
};

struct union_of_fams {
  unsigned long flags;
  union {

    DECLARE_BOUNDED_FLEX_ARRAY(int, count_bytes, unsigned char, bytes);
    DECLARE_BOUNDED_FLEX_ARRAY(unsigned char, count_ints, unsigned char, ints);
    DECLARE_FLEX_ARRAY(unsigned char, unsafe);
  };
};

struct anon_struct {
  unsigned long flags;
  size_t count;
  DECLARE_FLEX_ARRAY_COUNTED_BY(int, array, count);
};

void test1(struct annotated *p, int index, int val) { p->array[index] = val; }

void test2(struct annotated *p, size_t index) {
  p->array[index] = __builtin_dynamic_object_size(p->array, 1);
}

void test3(struct annotated *p, size_t index) {

  p->array[index] = __builtin_dynamic_object_size(p, 1);
}

void test4(struct annotated *p, int index, int fam_idx) {

  p->array[index] =
      (unsigned char)__builtin_dynamic_object_size(&p->array[3], 1);
  p->array[index + 1] =
      (unsigned char)__builtin_dynamic_object_size(&(p->array[4]), 1);
  p->array[index + 2] =
      (unsigned char)__builtin_dynamic_object_size(&(p->array[fam_idx]), 1);
}

void test5(struct anon_struct *p, int index) {
  p->array[index] = __builtin_dynamic_object_size(p, 1);
}

void test6(struct anon_struct *p, int index) {
  p->array[index] = __builtin_dynamic_object_size(p->array, 1);
}

void test7(struct union_of_fams *p, int index) {
  p->ints[index] = __builtin_dynamic_object_size(p, 1);
}

void test8(struct union_of_fams *p, int index) {
  p->ints[index] = __builtin_dynamic_object_size(p->ints, 1);
}

void test9(struct union_of_fams *p, int index) {
  p->bytes[index] = (unsigned char)__builtin_dynamic_object_size(p, 1);
}

void test10(struct union_of_fams *p, int index) {
  p->bytes[index] = (unsigned char)__builtin_dynamic_object_size(p->bytes, 1);
}

void test11(struct annotated *p, int index) {
  p->array[index] = __builtin_dynamic_object_size(&p->count, 1);
}