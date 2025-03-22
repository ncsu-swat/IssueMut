#include <arm_acle.h>

void cdp() { __arm_cdp(1, 2, 3, 4, 5, 6); }

void cdp2() { __arm_cdp2(1, 2, 3, 4, 5, 6); }

void ldc(int i) { __arm_ldc(1, 2, &i); }

void ldcl(int i) { __arm_ldcl(1, 2, &i); }

void ldc2(int i) { __arm_ldc2(1, 2, &i); }

void ldc2l(int i) { __arm_ldc2l(1, 2, &i); }

void stc(int i) { __arm_stc(1, 2, &i); }

void stcl(int i) { __arm_stcl(1, 2, &i); }

void stc2(int i) { __arm_stc2(1, 2, &i); }

void stc2l(int i) { __arm_stc2l(1, 2, &i); }

void mcr() { __arm_mcr(1, 2, 3, 4, 5, 6); }

void mcr2() { __arm_mcr2(1, 2, 3, 4, 5, 6); }

void mrc() { __arm_mrc(1, 2, 3, 4, 5); }

void mrc2() { __arm_mrc2(1, 2, 3, 4, 5); }

void mcrr() { __arm_mcrr(1, 2, 3, 4); }

void mcrr2() { __arm_mcrr2(1, 2, 3, 4); }

void mrrc() { __arm_mrrc(1, 2, 3); }

void mrrc2() { __arm_mrrc2(1, 2, 3); }
