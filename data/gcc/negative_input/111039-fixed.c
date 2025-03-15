int _setjmp();
void abcd();
void abcde();
void compiler_corruption_function(int flags) {
  int nowait;
  int isexpand;
  abcd();
  _setjmp(flags);
  nowait = flags & 1048576;
  isexpand = flags & 8388608;
  if (nowait && isexpand)
    flags &= 0;
  abcde();
}