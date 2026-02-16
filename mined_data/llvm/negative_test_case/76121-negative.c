#include <omp.h>
#include <stdio.h>

typedef int32_t kmp_int32;
typedef void *ident_t;
typedef void *kmpc_micro;

#ifdef __cplusplus
extern "C" {
#endif
extern void __kmpc_fork_call(ident_t *loc, kmp_int32 argc, kmpc_micro microtask,
                             ...);
#ifdef __cplusplus
}
#endif

void microtask(int *global_tid, int *bound_tid) {

  if (omp_in_parallel()) {
    printf("FAIL\n");
  } else {
    printf("PASS\n");
  }
}

int main() {

  int cond = 0;

  if (cond) {
    __kmpc_fork_call(NULL, 0, microtask, NULL);
  } else {
    microtask(NULL, NULL);
  }
  return 0;
}