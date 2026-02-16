vector int c, a, b;

static inline void __attribute__((__always_inline__, target("cpu=power8")))
foo() 
{
  c = a + b;
}

__attribute__((target("cpu=power8"))) int main() {
  foo(); 
  c = a + b;
}