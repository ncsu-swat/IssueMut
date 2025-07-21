#include <assert.h>

struct alignas(16) S {
  char bytes[16];
};

static_assert(alignof(struct S) == 16);