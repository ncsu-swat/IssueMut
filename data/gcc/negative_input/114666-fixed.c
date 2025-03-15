struct {
  signed a : 1;
} b = {-1};
char c;
int main() {
  unsigned long val = (unsigned long)b.a;
  if ((val ^ 1UL) < 3)
    __builtin_abort();
}