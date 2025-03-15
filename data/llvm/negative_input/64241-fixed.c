#ifdef SOFT_FLOAT_CONSTRAINT_R

void read_float(FLOAT *p) {
  FLOAT result = *p;
  __asm__("" ::"f"(result));
}
#endif