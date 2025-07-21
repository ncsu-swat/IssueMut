#include <stdalign.h>
struct alignas_test {
  char c;
  char alignas_8 alignas(8);
};