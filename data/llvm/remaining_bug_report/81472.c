#include <stdalign.h>
struct alignas_test {
  char c;
  char alignas(8) alignas_8;
};