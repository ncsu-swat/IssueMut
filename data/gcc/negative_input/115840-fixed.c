double loads[16] = {0};

void foo(double loadavg[], int count) {
  for (int i = 0; i < count; i++)
    loadavg[i] = loads[i] / 1.5;
}