__builtin_va_list FOO_showfatal_ap;
void FOO_showfatal(int fmta, ...) {
  __builtin_va_start(FOO_showfatal_ap, fmta);
}