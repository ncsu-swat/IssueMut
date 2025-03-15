int a, b, n;
int w;
void fun1(int t) {
  int tmp_a = a;
  int tmp_b = b;
  int sum = tmp_a + tmp_b;
  a = tmp_a + w * 100;
  b = tmp_b - w * 100;
  n = t + sum * 100;
}