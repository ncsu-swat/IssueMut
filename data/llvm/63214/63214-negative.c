inline int func2(int i);
int external_call2(int i) {
  
  
  return func2(i);
}

inline int func2(int i) { return 0; }