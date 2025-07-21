union _u {
  char a[0];
} u = {};
union _u0 {
  char a[0];
} u0 = {0};

union {
  char a[0];
} z = {};

union {
  char a[0];
} z0 = {0};

char keep(int pick) {
  if (pick)
    return z.a[0];
  else
    return z0.a[0];
}