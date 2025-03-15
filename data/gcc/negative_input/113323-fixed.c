typedef long __attribute__((__vector_size__(16))) V;
V u, v;
_BitInt(535) i;

void foo(void) {
  _BitInt(535) temp = i;
  int condition = temp != 0;
  while (condition) {
    u = v;
    temp--;
    condition = temp != 0;
  }
}