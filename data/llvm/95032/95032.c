#include <assert.h>

struct S {
  alignas(16) char bytes[16];
};

static_assert(alignof(struct S) == 16);