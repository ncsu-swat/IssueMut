#include <stdarg.h>
void foo(...) {
  va_list v;
  va_start(v);
  va_arg(v, int(*)[5]);
  va_end(v);
}
int main(void) { foo(&(int[]){1, 2, 3, 4, 5}); }