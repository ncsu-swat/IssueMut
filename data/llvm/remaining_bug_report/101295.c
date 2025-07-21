#include <stdio.h>

extern void outs(char *str);

void test(void) {
  char msgbuf[64];
  sprintf(msgbuf, "preemption imbalance ");
  outs(msgbuf);
}