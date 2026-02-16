
int TenElements[10];

int rng(void);
int getIndex(void) {
  switch (rng()) {
  case 1:
    return -152;
  case 2:
    return -160;
  case 3:
    return -168;
  default:
    return -172;
  }
}

void gh86959(void) {
  // Previously code like this produced many almost-identical bug reports that
  // only differed in the offset value. Verify that now we only see one report.

  // expected-note@+1 {{Entering loop body}}
  while (rng())
    TenElements[getIndex()] = 10;
  // expected-warning@-1 {{Out of bound access to memory preceding
  // 'TenElements'}} expected-note@-2 {{Access of 'TenElements' at negative byte
  // offset -688}}
}