
struct S11 {
  int len;
};
void ghissue112516() {
  struct S11 *s11 = 0;
  constexpr int num =
      s11->len; // expected-error {{constexpr variable 'num' must be initialized
                // by a constant expression}}
  void *Arr[num];
}
