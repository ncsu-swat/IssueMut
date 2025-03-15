unsigned char a, c;
unsigned short b;

void foo(void) {
  c = a + 255;
  b = c;
  while (++b > 255)
    ;
}