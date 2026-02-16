#include <stdint.h>
#include <stdio.h>

extern void nothing(double x);

void fn(__fp16 &x) { nothing((double)x); }

void fn(_Float16 &x) { nothing((double)x); }

void fnp(__fp16 &x) { printf("%a", (double)x); }

void fnp(_Float16 &x) { printf("%a", (double)x); }