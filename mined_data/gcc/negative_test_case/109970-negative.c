/* PR109970
 * { dg-do compile }
 * { dg-options "-Wstringop-overflow" }
 * */

void bar(int x, char buf[x]);
void foo(int x, char buf[x]);

int main() {
  char buf[10];
  bar(11, buf); /* { dg-warning "accessing 11 bytes in a region of size 10" } */
  foo(11, buf); /* { dg-warning "accessing 11 bytes in a region of size 10" } */
}