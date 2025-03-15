#include "callbacks.h"
#include <omp.h>
#include <stdio.h>

int main(void) {
  int M[10];
#pragma omp target enter data map(to : M[:10]) device(0)
#pragma omp target device(0)
  {
#pragma omp teams distribute parallel for simd
    for (int i = 0; i < 10; ++i) {
      M[i] = i;
    }
  }
#pragma omp target exit data map(from : M[:10]) device(0)
  return 0;
}