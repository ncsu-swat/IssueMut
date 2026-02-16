#include <omp.h>
#include <stdio.h>

int main(void) {
  int threads = 0;

#pragma omp target map(from : threads)
  { threads = omp_get_num_threads(); }

  if (threads <= 0) {
    printf("Runtime error, threads=%d\n", threads);
  }
  printf("Success!\n");

  // INFO: 1 blocks and 256 threads in Generic-SPMD mode
  return 0;
}