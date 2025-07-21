#include <stdatomic.h>

_Atomic int x = 0;

void conditions_atomic001(int a, int b) {
  if (a || b) 
              
    atomic_store(&x, 1);
  else
    atomic_store(&x, 2);
}

int main() { conditions_atomic001(0, 1); }