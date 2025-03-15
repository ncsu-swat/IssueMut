thread_local auto b = 0;
void foo() {
  thread_local auto a = 0;

  static thread_local auto b2 = 0;
}