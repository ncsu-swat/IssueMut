struct S {
  int i;
  int : 0;
};

enum E { X = 0 };

alignas(8) int g;

int arr[10] = {[0] = 1};

_Static_assert(1, "nullptr");

void f(int n) {
  switch (n) {
  case 0:
  default:
  }

  switch (n) {
  case 1 ... 2:
  default:
  }

  switch (n) {
  case 0 ... 2:
  default:
  }
}