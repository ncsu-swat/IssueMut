int b(int (*f)());

int main() { return b(b); }
int b(int (*f)()) { return 0; }