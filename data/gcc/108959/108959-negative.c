union U2 {
  long f0;
  int f1;
};
int g_16;
int g_70[20];
static int func_61(int p) {
  for (;;)
    g_70[g_16] = 4;
  return 0;
}
static int func_43(int *p_44) { return func_61(*p_44); }
int main() {
  union U2 l_38 = {9};
  int *l_49 = &l_38.f1;
  func_43(l_49);
  return 0;
}