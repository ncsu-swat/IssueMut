signed char a[] = {0x80, 0x80, 0x80, 0x80};
int b;
signed char c;

int main() {
  for (; b < sizeof(a); b += 1) {
    if (a[b] < 0) {
      c = 1;
    } else {
      c = a[b] >> 6;
    }
  }

  if (c != 1)
    __builtin_abort();
  return 0;
}