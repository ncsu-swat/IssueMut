static unsigned char xl[192] __attribute__((aligned(64)));
static unsigned char A170[192 * 3] __attribute__((aligned(64)));

void jerate(unsigned char *, unsigned char *);
float foo(unsigned n) {
  jerate(xl, A170);

  unsigned i = 32;
  int kr = 1;
  float sfn11s = 0.f;
  float sfn12s = 0.f;
  do {
    int krm1 = kr - 1;
    long j = krm1;
    float a = (*(float(*)[n])A170)[j];
    float b = (*(float(*)[n])xl)[j];
    float c = a * b;
    float d = c * 6.93149983882904052734375e-1f;
    float e = (*(float(*)[n])A170)[j + 48];
    float f = (*(float(*)[n])A170)[j + 96];
    float g = d * e;
    sfn11s = sfn11s + g;
    float h = f * d;
    sfn12s = sfn12s + h;
    kr++;
  } while (--i != 0);
  float tem = sfn11s + sfn12s;
  return tem;
}