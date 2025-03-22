int n;
void f(void) {
  switch (n) {
    case 0:
      [[fallthrough]]; 
                         
    case 1:;
  }
}