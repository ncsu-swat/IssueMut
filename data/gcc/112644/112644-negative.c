#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif
extern int printf(char const *, ...);
#ifdef __cplusplus
}
#endif
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __UINT64_TYPE__ uint64_t;

__attribute__((noinline)) void *Ident(void *argument) { return argument; }

void *pthread_stack_is_cleared(void *argument) {
  (void)argument;
  int internal_array[1] = {0};
  return Ident((void *)internal_array);
}

int main(int argc, char **argv) {
  int argument[100] = {0};
  argument[1] = 10;
  pthread_t thread_index;
  pthread_create(&thread_index, NULL, pthread_stack_is_cleared,
                 (void *)argument);

  void *retval;
  pthread_join(thread_index, &retval);

  printf("(should fail): ");
  printf("value left in stack is: %d\n", ((int *)retval)[0]);

  return (uintptr_t)retval;
}