__attribute__((target_clones("default", "arch=x86-64", "arch=x86-64-v2",
                             "arch=x86-64-v3", "arch=x86-64-v4"))) int
isa_level(int) {
  return 0;
}