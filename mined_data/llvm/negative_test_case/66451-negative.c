#include <stdio.h>
#include <stdlib.h>

/* Using stderr for all output or else godbolt doesn't intermix output. */
int main(int argc, char *argv[]) {
  char *p = NULL;

  fprintf(stderr, "%p (%zu)\n", p, (unsigned long)p);

  /* argc is a stand-in for "1" to avoid optimization */
  p -= argc;

  fprintf(stderr, "%p (%zu)\n", p, (unsigned long)p);

  p += argc;

  fprintf(stderr, "%p (%zu)\n", p, (unsigned long)p);

  return 0;
}