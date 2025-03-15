char *s1, *s2;
extern int *my_alloc(int);
extern int _setjmp();
extern void bar();
void foo(int s1len, int s2len) {
  int e;
  s1len++; // Moved increment before setjmp
  int *md = my_alloc(sizeof(int) * s1len * s2len);
  e = _setjmp();
  {
    int i = 0;
    while (i < s1len) {
      int k = 0;
      while (k < s2len) {
        int m = 0;
        while (m < s1len) {
          int j = 1;
          while (j < s2len) {
            int cost = (s1[1] == s2[1]) ? 0 : 1;
            md[j * s1len] = cost;
            j++;
          }
          m++;
        }
        k++;
      }
      i++;
    }
    bar();
  }
}