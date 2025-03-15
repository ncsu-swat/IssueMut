void test_omp_barrier() {
#pragma omp parallel
  {
#pragma omp task
    {}
#pragma omp taskwait
  }
}

int main() { test_omp_barrier(); }