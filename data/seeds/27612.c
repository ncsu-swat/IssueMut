/* { dg-do compile } */

#include <stdlib.h>
#include <string.h>
void treathead() {
  char *a = ';' == '\0' ?: 0;
  if (*a == '=') {
    while (*a == (*a == 0) || *a == '\'')
      a++;
    if (strlen(a) < 2)
      abort();
  }
}
