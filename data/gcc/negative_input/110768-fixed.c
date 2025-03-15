int a;
void foo();
void bar64_(void) {}

int main() {
  signed char b = a = 6;
  for (; a; a = 0) {
    bar64_();
    b = 0;
  }
  if (b <= 0)
    ;
  else
    foo();
}