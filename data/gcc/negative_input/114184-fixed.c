/* PR target/114184 */
/* { dg-do compile } */
/* { dg-options "-Og -mavx2" } */

_Complex long double foo(void) {
  union {
    _Complex long double d;
    unsigned char bytes[32];
  } u = {.bytes = {149, 136, 89, 42, 38, 240, 196, 194}};
  return u.d;
}

long double bar(void) {
  union {
    long double d;
    unsigned char bytes[16];
  } u = {.bytes = {149, 136, 89, 42, 38, 240, 196, 194}};
  return u.d;
}