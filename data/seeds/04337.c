/* Check that we properly report mmap failure. */

/* { dg-do run { target setrlimit } } */
/* { dg-skip-if "" { *-*-* } { "*" } { "-O0" } } */
/* { dg-require-effective-target hw } */
/* { dg-shouldfail "asan" } */

#include <assert.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

static volatile void *x;

int main(int argc, char **argv) {
  struct rlimit mmap_resource_limit = {0, 0};
  if (setrlimit(RLIMIT_AS, &mmap_resource_limit))
    return 1;
  x = malloc(10000000);
  return 0;
}

/* { dg-output "ERROR: Failed to mmap" } */
