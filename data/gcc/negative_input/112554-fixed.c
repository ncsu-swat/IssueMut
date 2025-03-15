int a;
void b() {
  unsigned long c = 18446744073709551612UL;
  while (c) {
    --c;
    a ^= c;
  }
}