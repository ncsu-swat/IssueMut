#include <limits.h>

#define vector __attribute__((vector_size(sizeof(unsigned) * 2)))

vector signed and1(vector unsigned x, vector unsigned y) {
  return (x != 0) & (x > y);
}

vector signed and2(vector unsigned x, vector unsigned y) {
  return (x != UINT_MAX) & (x < y);
}

vector signed and3(vector signed x, vector signed y) {
  return (x != INT_MIN) & (x > y);
}

vector signed and4(vector signed x, vector signed y) {
  return (x != INT_MAX) & (x < y);
}