int a, b, c, d;
unsigned char e[1] = {1};

int main() {
  for (a = 0; a < 3; a++)
    for (b = 0; b < 2; b++)
      c = e[0] = e[0] ^ d;
  if (!c)
    __builtin_abort();
  return 0;
}