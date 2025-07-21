#include <stdio.h>
#include <string.h>

#define report(x) printf(#x ": %zu\n", x)

struct foo {
  size_t count;
  int some[3];
};

static struct foo instance = {
    .count = 3,
    .some =
        {
            5,
            10,
            15,
        },
};

int main() {
  report(sizeof(struct foo));
  report(sizeof(instance));
  report(__builtin_object_size(&instance, 1));
  report(__builtin_dynamic_object_size(&instance, 1));

  printf("%d\n", instance.some[2]);

  return 0;
}