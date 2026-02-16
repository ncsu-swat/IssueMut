void clang_analyzer_dump_ptr(const unsigned char *ptr);
void clang_analyzer_dump(unsigned char val);

int main() {
  const unsigned char SelfBytes[] = {
#include "embed.c"
  };
  clang_analyzer_dump_ptr(SelfBytes);
  clang_analyzer_dump(SelfBytes[0]);
}