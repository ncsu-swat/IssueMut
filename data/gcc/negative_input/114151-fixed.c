typedef int int32_t __attribute__((mode(__SI__)));

void bar(int32_t);

void foo() {
  int32_t index = 0;
  int32_t base = 0xcafe;
  int32_t mult = 0xdead;

  for (index; index <= 10; index--)
    bar(base * mult + index * mult);
}