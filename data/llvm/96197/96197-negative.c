__attribute__((target_version("simd"))) void helper(void) {}

__attribute__((target_version("default"))) void helper(void) {}

int main() { helper(); }