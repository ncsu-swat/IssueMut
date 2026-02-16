// clang -fopenmp t1.c -o t1 && OMP_WAIT_POLICY=passive
// KMP_FORKJOIN_BARRIER_PATTERN='dist,dist' ./t1
void test_omp_barrier() {
#pragma omp parallel
  {
#pragma omp task
    {}
  }
}

int main() { test_omp_barrier(); }