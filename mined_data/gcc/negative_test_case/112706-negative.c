int *ptr;
void link_error();
void test() {
  int *ptr1 = ptr + 10;
  int *ptr2 = ptr + 20;
  if (ptr1 - ptr2 == 0)
    link_error();
}