// RUN: %clang_analyze_cc1 %s -triple=x86_64-unknown-linux \
// RUN:   -verify -Wno-error=implicit-function-declaration \
// RUN:   -analyzer-checker=core,unix.Malloc,debug.ExprInspection \
// RUN:   -analyzer-config core.CallAndMessage:ArgPointeeInitializedness=true
//
// Just exercise the analyzer on code that has at one point caused issues
// (i.e., no assertions or crashes).

void clang_analyzer_dump_int(int);

// Reproduce crash from GH#94496. When array is used as subcript to another
// array, CSA cannot model it and should just assume it's unknown and do not
// crash.
void f4(char *array) {
  char b[4] = {0};

  _Static_assert(sizeof(int) == 4, "Wrong triple for the test");

  clang_analyzer_dump_int(
      __builtin_bit_cast(int, b)); // expected-warning {{lazyCompoundVal}}
  clang_analyzer_dump_int(
      array[__builtin_bit_cast(int, b)]); // expected-warning {{Unknown}}

  array[__builtin_bit_cast(int, b)] = 0x10; // no crash
}
