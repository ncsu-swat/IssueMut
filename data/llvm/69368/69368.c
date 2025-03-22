int main() {
  int a[2];
  int attempt = 0;

#pragma omp parallel for
  for (int i = 0; i < 2; i++) {
    a[i] = 2;
  }

#pragma omp teams distribute parallel for if (attempt >= 2)
  for (int i = 0; i < 2; i++) {
    a[i] = 1;
  }
  return 0;
}