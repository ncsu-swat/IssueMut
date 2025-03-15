struct _NMPObject {
  int ifindex;
  char network_ptr[];
};

union {
  int x;
  struct _NMPObject k;
} foo = {.x = 0};