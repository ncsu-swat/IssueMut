int main() {
  static volatile _Atomic(long double) a = 0;
  (a) == 1;
}