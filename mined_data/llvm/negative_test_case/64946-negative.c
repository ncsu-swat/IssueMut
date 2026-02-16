#include <assert.h>
#include <stdlib.h>

int main(void) {
  char *end;
  long l = strtol("42", &end, 10);
  assert(l == 42);
  assert(*end == '\0');
  return 0;
}