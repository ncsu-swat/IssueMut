int func_7_uc_10li_19(int);
int li_4, li_5, us_8;
unsigned char func_7_ptr_13, func_7_uc_14;
long t;
void func_7_ptr_18() {
  if (li_5) {
    for (;;)
      ;
    short s_15;
    for (; func_7_uc_14;) {
      us_8 = 7;
      for (; us_8; us_8 += 1)
      lblD2AF1FAB:
        if (us_8)
          li_4 = 1;
      func_7_uc_14 += t;
      if (func_7_ptr_13 & 1 && (func_7_uc_14 &= func_7_ptr_13))
        s_15 %= func_7_uc_10li_19(s_15);
    }
  }
  goto lblD2AF1FAB;
}