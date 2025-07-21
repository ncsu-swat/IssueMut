int a;
long b;
int *c = &a;
short d(short e, short f) { return e * f; }
void foo() { *c = (int)d(340, b >= 0) ^ 3; }