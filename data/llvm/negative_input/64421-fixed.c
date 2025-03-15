#include <omp.h>
#include <stdio.h>

int main(void) {
  int threads = 0;

#pragma omp target map(from : threads) num_threads(1)
  { threads = omp_get_num_threads(); }

  if (threads <= 0) {
    printf("Runtime error, threads=%d\n", threads);
  }
  printf("Success!\n");

  
  return 0;
}