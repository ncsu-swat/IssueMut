struct c {
  virtual ~c();
};
struct d : c {};
class a : d {};
a f;