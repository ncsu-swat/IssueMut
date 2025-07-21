struct has_array {
  int a;
  int b[4];
  int c;
};

int access(struct has_array *p, int index) { return p->b[index]; }