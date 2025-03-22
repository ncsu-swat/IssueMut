template <typename T, typename ARGS>
static inline T * construct_at(void *at, ARGS && args)
{
 struct Placeable : T
 {
  Placeable(ARGS && args) : T(args) { }
  void * operator new (long unsigned int, void *ptr) { return ptr; }
  void operator delete (void *, void *) { }
 };
 return new (at) Placeable(static_cast<ARGS &&>(args));
}
template <typename MT>
struct Reconstructible
{
  char _space[sizeof(MT)];
  Reconstructible() { }
};
template <typename MT>
struct Constructible : Reconstructible<MT>
{
 Constructible(){}
};
struct A { };
struct B
{
 Constructible<A> a { };
 B(int) { }
};
Constructible<B> b { };
void f()
{
  enum { ENUM_A = 1 };
  enum { ENUM_B = 2 };
  construct_at<B>(b._space, ENUM_B);
}