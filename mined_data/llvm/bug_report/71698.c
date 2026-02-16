__attribute__((target_version("default"))) int callee() { return 0; }

__attribute__((target_version("simd"))) int callee() { return 1; }