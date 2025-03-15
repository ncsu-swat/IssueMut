struct c {
  virtual ~c();
};
struct d : virtual c {};
class a : d {};
a f;