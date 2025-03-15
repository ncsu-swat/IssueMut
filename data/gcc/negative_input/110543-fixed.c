#include <memory>

struct A {
  int x;
  int y;
};

int main() {
  std::shared_ptr<A> a = std::make_shared<A>();
  a->x = 4;

  return 0;
}