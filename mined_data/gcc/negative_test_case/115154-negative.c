struct s {
  signed b : 1;
} f;
int i = 55;
__attribute__((noinline))
void check(int a)
{
        if (!a)
        __builtin_abort();
}
int main() {
    int t = i != 5;
    t = t*5;
    if (t >= 0) {
        f.b = t;
    } else {
        f.b = 0;
    }
    int tt = f.b;
    check(f.b);
}