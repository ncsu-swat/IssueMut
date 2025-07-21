struct {
  signed a : 1;
} b = {-1};
char c;
int main() {
  if (((long)b.a ^ 1UL) < 3)
    __builtin_abort();
}