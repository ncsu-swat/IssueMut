// RUN: %clang_cc1 -std=c23 -fsyntax-only -verify %s
// RUN: %clang_cc1 -fsyntax-only -verify -x c++ -Wno-c23-extensions %s
// expected-no-diagnostics

static const char data1[] = {
#embed __FILE__
};

char *p1 = (char *)data1;

static const int data2[] = {
#embed __FILE__
};

char *p2 = (int *)data2;

static const int data3[30] = {
#embed __FILE__ limit(30)
};
int *p3 = (int *)data3;
