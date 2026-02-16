#pragma GCC target("arch=rv64gc_zve64d")

long a[100], b[100], c[100];

#pragma GCC optimize("no-tree-slp-vectorize")
void g1() {
  for (int i = 0; i < 100; i += 2) {
    c[i] += a[b[i]] + 1;
    c[i + 1] += a[b[i + 1]] + 2;
  }
}

#pragma GCC optimize("no-tree-slp-vectorize")
long g2() {
  long res = 0;
  for (int i = 0; i < 100; i += 2) {
    res += a[b[i + 1]];
    res += a[b[i]];
  }
  return res;
}

#pragma GCC optimize("no-tree-slp-vectorize")
long g3() {
  long res = 0;
  for (int i = 0; i < 100; i += 2) {
    res += a[b[i]];
    res += a[b[i + 1]];
  }
  return res;
}