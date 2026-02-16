float sqrtf(float x);
float powf(float x, float y);
float fmaf(float x, float y, float z);
char *rindex(const char *s, int c);

#pragma float_control(push)
#pragma float_control(precise, off)

float fp_precise_off_libm_calls(float a, float b, float c, const char *d,
                                char *e, unsigned char f) {
  a = __builtin_sqrtf(a);
  a = __builtin_powf(a, b);
  a = fmaf(a, b, c);
  e = rindex(d, 75);
  return a;
}
#pragma float_control(pop)

#pragma float_control(push)
#pragma float_control(precise, on)

float fp_precise_on_libm_calls(float a, float b, float c, const char *d,
                               char *e, unsigned char f) {
  a = sqrtf(a);
  a = powf(a, b);
  a = fmaf(a, b, c);
  e = rindex(d, 75);
  return a;
}
#pragma float_control(pop)