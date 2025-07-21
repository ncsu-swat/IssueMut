#include <stdarg.h>
void foo(void *first, ...) {
  va_list v;
  va_start(v, first);
  va_arg(v, int(*)[5]);
  va_end(v);
}
int main(void) { foo(&(int[]){1, 2, 3, 4, 5}); }