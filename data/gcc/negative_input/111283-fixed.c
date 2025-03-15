__attribute__((noipa)) static void edge(void) {}

int p = 1;

__attribute__((noinline)) static void rule1(void) {
  if (p)
    edge();
}

__attribute__((noinline)) static void rule1_same(void) {
  if (p)
    edge();
}

__attribute__((noipa)) int main(void) {
  rule1();
  rule1_same();
}