// RUN: %clang_analyze_cc1 -analyzer-checker=core,debug.ExprInspection -verify
// %s

void clang_analyzer_dump(char);
void clang_analyzer_dump_ptr(void *); // use `void*` to match &&label's type

void binding_to_label_loc_circumvented() {
  void *b = &&MyLabel;        // keep label address, but use correct type
  clang_analyzer_dump_ptr(b); // expected-warning {{&&MyLabel}}

MyLabel:
}
