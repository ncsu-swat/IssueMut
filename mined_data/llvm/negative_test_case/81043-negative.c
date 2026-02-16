__attribute__((target_clones("fp16", "fp16fml", "default"))) void foo(void);

void caller() { foo(); }