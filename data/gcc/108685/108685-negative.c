void foo(int a) {
#pragma omp for collapse(2) ordered(4)
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < a; j++)
        for (int k = 0; k < 2; k++)
          for (int l = 0; l < a; l++) {
#pragma omp ordered depend(source)
            __builtin_abort();
          }
}