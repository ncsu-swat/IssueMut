void f() {
  (void)"foo()foo";
  (void)L"foo()foo";

#ifdef UNICODE
  (void)u"foo()foo";
  (void)u8"foo()foo";
  (void)U"foo()foo";
#endif
}

#define R "bar"
const char *s = "foo(";