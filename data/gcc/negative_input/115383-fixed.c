#include "tree-vect.h"

int __attribute__((noipa)) s331(int start, int n) {
  int j = 0;
  int i = start;
  while (i < n) {
    if ((float)i < 0.0f)
      j = i;
    i++;
  }
  return j;
}

int main() {
  check_vect();
  int j = s331(-13, 17);
  if (j != -1)
    abort();
  return 0;
}