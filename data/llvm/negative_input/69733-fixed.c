#include <omp.h>
int main() {
#pragma omp parallel num_threads(1)
  {
#pragma omp single
    {
      omp_event_handle_t ev;
#pragma omp task detach(ev)
      {}
      omp_fulfill_event(ev);
    }
  }
}