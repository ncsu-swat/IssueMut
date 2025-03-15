_Thread_local auto b = 0;
void foo() {
  _Thread_local auto a = 0;

  static _Thread_local auto b2 = 0;
}