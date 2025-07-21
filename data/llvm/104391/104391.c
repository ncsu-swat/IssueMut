[[nodiscard]] int f3();

void GH104391() {
#define M (unsigned int)f3()
  M; // expected-warning {{ignoring return value of function declared with
     // 'nodiscard' attribute}}
}