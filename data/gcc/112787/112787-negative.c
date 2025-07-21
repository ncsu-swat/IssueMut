typedef int __attribute__((__vector_size__(64))) vec;

__attribute__((target("no-sve")))
vec fn(vec a, vec b) { return a + b; }