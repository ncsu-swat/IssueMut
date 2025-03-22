int x;

void foo(int i, unsigned u) { x = __builtin_mul_overflow_p(u, i, 0U); }

int main() { foo(11, 0); }