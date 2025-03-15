/* { dg-do compile } */
/* { dg-options "-O" } */

/* common */
char c;
/* arrays must be 8 byte aligned, regardless of size */
char c_ary[1];

/* data */
char d = 1;
char d_ary[1] = {1};

int main() {
  unsigned long addr1 = (unsigned long)&c_ary[0];
  if ((addr1 & 7) != 0)
    return 1;
  unsigned long addr2 = (unsigned long)&d_ary[0];
  if ((addr2 & 7) != 0)
    return 1;
  return 0;
}