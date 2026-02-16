#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void example_1(void) {
  char b[2000];
  FILE *f = fopen("dbl_cls.c", "r"); 
  if (f) {
    b[0] = 0;
    fread(b, 1, sizeof(b) - 1, f);
    printf("%s\n'", b);
    int r1 = fclose(f); 
    f = NULL;
    printf("\n-----------------\n1 close done '%d'\n", r1);

    int r2 = fclose(f); 
    printf("2 close done '%d'\n", r2);
  }
}