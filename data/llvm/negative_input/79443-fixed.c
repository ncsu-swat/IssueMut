typedef __typeof__(sizeof(0)) size_t;

extern void free(void *);
extern void *malloc(size_t size);

void cleanup_free(void **p) { free(*p); }

void t8(void) { void *p __attribute__((cleanup(cleanup_free))) = malloc(10); }
typedef __attribute__((aligned(2))) int Aligned2Int;
void t9(void) { Aligned2Int __attribute__((cleanup(c1))) xwarn; }

__attribute__((enforce_tcb("TCB1"))) void func1(int *x) { *x = 5; }
__attribute__((enforce_tcb("TCB2"))) void t10() {
  int __attribute__((cleanup(func1))) x = 5;
}