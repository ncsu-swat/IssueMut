#include <stdio.h>
void run(int teams, int th) {
#pragma omp teams parallel num_teams(teams) num_threads(th)
#pragma omp task
  {}
}
int main() {
  fprintf(stderr, "run(1, 2)\n");
  run(1, 2);
  fprintf(stderr, "run(1, 3)\n");
  run(1, 3);
}