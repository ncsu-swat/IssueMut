#include <omp.h>
#include <stdio.h>

int main(void) {
#pragma omp parallel
  {
#pragma omp task
    {}
    printf("max prio = %d\n", omp_get_max_task_priority());
  }
  return 0;
}