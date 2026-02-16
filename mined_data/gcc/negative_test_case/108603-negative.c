long long a[128];
long long *p;
void f() {
  for (long i = 0; i < sizeof(long); i++)
    p[i] = a[i];
}