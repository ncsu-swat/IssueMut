/* { dg-do compile { target float128 } } */
/* { dg-options "-Wabsolute-value" } */

#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

void tst_float128_size(_Float128 *pf128) {
  *pf128 = fabsl(*pf128); /* { dg-warning "may cause truncation of value" } */
}
