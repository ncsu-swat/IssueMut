__attribute__((target("mcpu=v4"))) void foo() {
  signed int x = 5;
  signed int y = 2;
  signed int z = x / y;
}