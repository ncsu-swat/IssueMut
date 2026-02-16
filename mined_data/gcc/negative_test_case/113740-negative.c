/* PR c/113740 */
/* { dg-do compile { target bitint } } */
/* { dg-options "-std=c23" } */

struct S {
  int : 0;
};