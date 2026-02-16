void foo() {
  register void *ra asm("ra");
  asm volatile("# " : : : "ra", "memory");
}