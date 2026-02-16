typedef int int32_t __attribute__((mode(__SI__)));

void bar(int32_t);

void foo() {
  int32_t index = 0;

  for (index = 10; index >= 0; index--)

    bar((0xcafe + index) * 0xdead);
}