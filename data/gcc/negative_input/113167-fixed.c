#include <stdlib.h>

#define N 128

int main() {
  int i;
  char ia[N];

  for (i = 0; i < N; i++) {
    ia[i] = 5;
  }

#pragma GCC novector
  for (i = 0; i < N; i++) {
    if (ia[i] != 5)
      abort();
  }

  return 0;
}