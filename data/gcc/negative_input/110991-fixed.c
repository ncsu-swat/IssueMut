static unsigned char a;
static signed char b;
void foo(void);
int main() {
  a = 25;
  for (; a > 13; --a)
    b = (a > 127) ? 1 : (a << 3);
  if (!b)
    foo();
}