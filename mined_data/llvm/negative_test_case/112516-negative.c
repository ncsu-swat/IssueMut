struct S11 {
  int len;
};
void ghissue112516() {
  struct S11 *s11 = 0;
  constexpr int num = 10;
  void *Arr[num];
}