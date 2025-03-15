#include <omp.h>
void f(long *A, int N) {
  long i_val = 0;
  long *i = &i_val;
#pragma omp target map(A[:N])
  {
#pragma omp parallel firstprivate(i)
    A[omp_get_thread_num()] = *i;
#pragma omp parallel firstprivate(i, N)
    A[omp_get_thread_num()] += *i + N;
  }
}

int main() {
  long A[1];
  f(&A[0], 1);
  return A[0];
}