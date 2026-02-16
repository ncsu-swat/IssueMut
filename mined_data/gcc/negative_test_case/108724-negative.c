int a[16], b[16], c[16];
void foo() {
  for (int i = 0; i < 16; i++) {
    *(volatile int *)&a[i] = b[i] + c[i];
  }
}