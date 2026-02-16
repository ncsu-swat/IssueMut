/* PR c/109409 */
/* { dg-do compile } */
/* { dg-options "-Wall" } */

void foo(int n) {
  const char c[n];
  __builtin_strcpy(c, "1");
  __builtin_printf(c);
}