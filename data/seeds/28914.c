#define _GNU_SOURCE
#include <float.h>
#include <math.h>

int isnansf(float x) { return issignaling(x) ? 1 : 0; }
int isnans(double x) { return issignaling(x) ? 1 : 0; }
int isnansl(long double x) { return issignaling(x) ? 1 : 0; }
