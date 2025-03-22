struct T {
  int x : 32;
} v;
void f1(int x) {
  while (v.x - ((v.x <<= 1) - v.x))
    ;
}