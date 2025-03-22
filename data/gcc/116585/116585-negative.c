/* { dg-do compile } */

char *s1, *s2;
extern int *my_alloc(int);
extern int _setjmp();
extern void bar();
void foo(int s1len, int s2len) {
  int e;
  e = _setjmp();
  {
    int l, i;
    int *md = my_alloc(((sizeof(int)) * (s1len + 1) * (s2len)));
    s1len++;
    for (l = 0; 0 < s1len; l++)
      for (l = 0; 0 < s2len; l++)
        for (i = 0; 0 < s1len; i++) {
          int j = 1;
          for (j = 1; j < s2len; j++) {
            int cost;
            if (s1[1] == s2[1])
              cost = 0;
            else
              cost = 1;
            md[j * s1len] = ((cost));
          }
        }
    bar();
  }
}