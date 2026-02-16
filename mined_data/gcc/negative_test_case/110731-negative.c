__int128 foo(void) {
  struct S {
    __int128 f : 119;
  } s = {((__int128)-18014398509481984) << 64};
  return s.f >> 1;
}

int main() {
  if (foo() != (((__int128)-9007199254740992) << 64))
    __builtin_abort();
}