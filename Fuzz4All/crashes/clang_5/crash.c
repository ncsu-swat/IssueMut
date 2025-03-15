#include <stdlib.h>
int main(int argc, char
**argv) {}
 
#include <stddef.h>
#ifdef __cplusplus
#error "don't"
#endif
int main(int argc, char **argv) { size_t n; int xs[n]; }
 
#include <limits.h>
_Static_assert(sizeof(_Generic((typeof(INFINITY)0), float:1)) == 5, "Don't!");
 
#include <stdalign.h>
static _Static_assert(alignof(x) == N, "Check all alignment");
 
#include <stdalign.h>
_Static_assert(alignof(_Generic((int[]){1}, typeof(*(int[]){0}):1)) == 4, "Don't!");
 
#include <stddef.h>
_Static_assert(sizeof(((double[2][3]){{{{}, {}}}})[0][0]) == 64, "Useful!");
 
 
#include <stdlib.h>
char *x = malloc(1);
assert(x);  
free(x);  
char *y = calloc(1, 1);
assert(y);  
memset(x, 1, 1); /* memory was
