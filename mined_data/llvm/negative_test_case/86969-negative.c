int TenElements[10];

int rng(void);
int getIndex(void) { return -152; }

void gh86959(void) {

  while (rng())
    TenElements[getIndex()] = 10;
}