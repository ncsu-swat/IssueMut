struct S1 {
  unsigned a : 2
} b() {
  struct S1 l_2003[5][4] = {};
  l_2003[4][0].a;
}
int main() { b(); }