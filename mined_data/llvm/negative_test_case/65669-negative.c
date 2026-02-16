int __attribute__((target_version("fp+aes+pmull+rcpc"))) unspec_args(void) {
  return -1;
}
int __attribute__((target_version("default"))) unspec_args(void) { return 0; }
int cargs() { return unspec_args(); }