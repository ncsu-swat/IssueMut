#include <omp.h>
#include <stdio.h>
#include <assert.h>

// Tool related code is omitted for brevity but is identical to the original.
// It sets up the OMPT callbacks to observe runtime events.

/* Main program that does not manifest the bug */
int main(void) {
#pragma omp target
  {
    // This target region does not map any data, so it will not trigger
    // the ompt_target_data_alloc callback, thus avoiding the bug.
    printf("Executed on target device without data mapping.\n");
  }
  return 0;
}