unsigned f1(int t, int t1) {
  int tt = 0;
  if (t)
    tt = (t1 >> 3) & 1;
  return tt;
}
struct f {
  unsigned t : 3;
  unsigned t1 : 4;
};
unsigned f2(int t, struct f y) {
  int tt = 0;
  if (t)
    tt = y.t1;
  return tt;
}