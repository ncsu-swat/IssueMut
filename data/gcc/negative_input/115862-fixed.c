/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcv_zvl512b -mabi=lp64d" } */

struct mallinfo2 {
  int arena;
  int ordblks;
  int smblks;
  int hblks;
  int hblkhd;
  int usmblks;
  int fsmblks;
  int uordblks;
  int fordblks;
  int keepcost;
};

struct mallinfo {
  int arena;
  int ordblks;
  int smblks;
  int hblks;
  int hblkhd;
  int usmblks;
  int fsmblks;
  int uordblks;
  int fordblks;
  int keepcost;
};

struct mallinfo __libc_mallinfo(void) {
  struct mallinfo m;
  struct mallinfo2 m2;

  m = *(struct mallinfo *)&m2;

  return m;
}

/* { dg-final { scan-assembler {vle32\.v} } } */