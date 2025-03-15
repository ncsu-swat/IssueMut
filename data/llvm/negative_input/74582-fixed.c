#pragma omp begin declare target
char BigUninitializedBuffer[4096 * 64];
#pragma omp end declare target

int main() {
#pragma omp target
  {}
}