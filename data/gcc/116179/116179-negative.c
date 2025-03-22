/* { dg-additional-options "-fcompare-debug" } */

/* PR rtl-optimization/116179 */

struct g *b;
struct g {};
void *operator new(__SIZE_TYPE__, void *);
enum c { ZERO, ONE };
struct d : g{} * e;
c f;
struct h {
  g *k() {
    d *a = nullptr;
    c i = ZERO;
    if (a || i == ZERO || i == ONE)
      if (e || f)
        return 0;
    return new (&j) d;
  }
  void n();
  g j;
};
void h::n() {
  for (g *l(b), *m(b); l; l = m, m = nullptr)
    k();
}