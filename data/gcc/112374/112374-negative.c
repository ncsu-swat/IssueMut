struct t {
  long coef[1];
  t(const unsigned long &a) : coef{(long)a} {};
  t(const t &a);
};
extern void gen_int_mode(t, int);
struct expand_vec_perm_d {
  unsigned char perm[64];
  int vmode;
  unsigned char nelt;
};
void expand_vec_perm_blend(struct expand_vec_perm_d *d) {
  unsigned long mask = 0;
  for (unsigned i = 0; i < 4; ++i) {
    if (d->perm[i] >= 4)
      mask |= 3UL << (i * 2);
  }
  gen_int_mode(mask, 0);
}