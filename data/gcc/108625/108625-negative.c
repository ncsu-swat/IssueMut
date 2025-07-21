unsigned char foo(int x) {
  unsigned int t = -x;
  unsigned char t1 = t;
  unsigned char t2 = t;
  
  return t1 + t2;
}