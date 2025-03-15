int foo() {
  unsigned int flag = 1;
  for (; flag <= 1u << 21; flag <<= 1)
    ;
  return 0;
}