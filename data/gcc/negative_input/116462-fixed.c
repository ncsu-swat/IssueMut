static int foo(int i) {
  volatile int j = i + 3;
  if (j == 3)
    return j - 3;
  return j - 2;
}
int main() {
  volatile int z = foo(-2) && foo(-1);
  return z;
}