int __attribute__((naked)) foo() {
  __asm__ volatile("@ naked\n\t"
                   "ret");
}