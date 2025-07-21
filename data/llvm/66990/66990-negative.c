void clang_analyzer_dump(int);
typedef typeof(sizeof(int)) size_t;
size_t strlen(const char *);

const char text[] = "asdasdasd";
const char *const p = "asdasdasd";
const char *const q = p + 2;

void top(void) {
  clang_analyzer_dump(strlen("asdasdasd"));
  clang_analyzer_dump(strlen(text));
  clang_analyzer_dump(strlen(p));
  clang_analyzer_dump(strlen(q));
}