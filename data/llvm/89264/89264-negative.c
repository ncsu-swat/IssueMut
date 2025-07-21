void clang_analyzer_warnIfReached(void);

void binding_to_label_loc() {
  char c;
  char *b = &c;
MyLabel:
  *b = 0;

  clang_analyzer_warnIfReached();
}