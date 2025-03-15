
void clang_analyzer_eval(int);
void symbolic_longlong_and_int0(long long len) {
  char *a = malloc(5);
  (void)a[len + 1]; // no-warning
  // len: [-1,3]
  clang_analyzer_eval(-1 <= len && len <= 3); // expected-warning {{TRUE}}
  clang_analyzer_eval(0 <= len);              // expected-warning {{UNKNOWN}}
  clang_analyzer_eval(len <= 2);              // expected-warning {{UNKNOWN}}
}
