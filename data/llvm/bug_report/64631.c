static int __attribute__((target_clones("default,avx")))
has_target_clones(void) {
  return 0;
}
int main(void) { return has_target_clones(); }