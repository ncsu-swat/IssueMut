#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int a;
  omp_set_max_active_levels(1);

#pragma omp parallel num_threads(2)
  {
#pragma omp atomic
    a++;
  }

#pragma omp parallel num_threads(1)
  {
#pragma omp target nowait
    { a++; }
  }

  return EXIT_SUCCESS;
}