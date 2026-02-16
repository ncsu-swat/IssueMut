
void test_bool_assign(void) {
  int res;

  // Reproduce issue from GH#111147. __builtin_*_overflow funcions
  // should return _Bool, but not int.
  _Bool ret = __builtin_mul_overflow(10, 20, &res); // no crash
}