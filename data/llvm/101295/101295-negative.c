#include <stdio.h>
#include <string.h>

extern void outs(char *str);

void test(void) {
  char msgbuf[64];
  strcpy(msgbuf, "preemption imbalance ");
  outs(msgbuf);
}