double f_output_constraint_2(void) {
  double result;
  __asm("foo1" : "+f"(result));
  return result;
}