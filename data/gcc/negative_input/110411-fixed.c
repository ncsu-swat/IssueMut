#include <string.h>

struct s {
  long a;
  long b;
  long c;
  long d : 1;
};
unsigned long ptr;

void bug(struct s *dst) {
  struct s *src = (struct s *)ptr;
  memcpy(dst, src, sizeof(struct s));
}