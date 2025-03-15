struct S {
  int f0;
  int f1[];
};

typedef struct S S;

S s = {1, {2, 3}};