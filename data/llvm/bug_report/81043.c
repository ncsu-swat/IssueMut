__attribute__((target_version("fp16"))) void foo(void);

__attribute__((target_version("fp16fml"))) void foo(void);

__attribute__((target_version("default"))) void foo(void);

void caller() { foo(); }