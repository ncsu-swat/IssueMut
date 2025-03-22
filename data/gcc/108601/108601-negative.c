/* { dg-do compile } */
/* { dg-options "-O3 -fprofile-generate -mcpu=neoverse-v1" } */

int foo() {
  int limit = 1 << 21;
#pragma some_pragma
  int flag = 1;
  for (; flag <= limit; flag <<= 1)
    ;
  return 0;
}