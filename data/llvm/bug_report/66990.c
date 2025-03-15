void clang_analyzer_dump(int);
typedef typeof(sizeof(int)) size_t;
size_t strlen(const char *);

const char text[] = "asdasdasd";
const char * p = "asdasdasd";
const char * q = p + 2;

void top(void) {
  clang_analyzer_dump(strlen("asdasdasd")); // should be 9
  clang_analyzer_dump(strlen(text));        // should be 9
  clang_analyzer_dump(strlen(p));           // should be 9
  clang_analyzer_dump(
      strlen(q)); // ideally, it should be 7, but it's fine if we don't know.
}
