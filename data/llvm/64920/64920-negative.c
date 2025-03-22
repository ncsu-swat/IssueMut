#include <stdlib.h>

void clang_analyzer_eval(int);
void symbolic_longlong_and_int0(size_t len) {
  char *a = malloc(5);
  (void)a[len + 1]; 
  
  clang_analyzer_eval(-1 <= len && len <= 3); 
  clang_analyzer_eval(0 <= len);              
  clang_analyzer_eval(len <= 2);              
}