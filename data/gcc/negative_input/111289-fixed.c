#include <stdarg.h>
#include <stdint.h>

typedef unsigned int mode_t;

extern void openat(int, const char *, int, mode_t);

static void test_1(char const *name, ...) {
  va_list arg;
  va_start(arg, name);

  mode_t mode = va_arg(arg, mode_t);

  va_end(arg);
  openat(-42, name, 0, mode);
}

void call_test_1() { test_1("nonexist.ent/", (mode_t)0600); }

int16_t global_2;

static void test_2(char const *name, ...) {
  va_list arg;
  va_start(arg, name);

  global_2 = va_arg(arg, int16_t);

  va_end(arg);
}

void call_test_2() { test_2("nonexist.ent/", (int16_t)42); }

long long global_3;

static void test_3(char const *name, ...) {
  va_list arg;
  va_start(arg, name);

  global_3 = va_arg(arg, long long);

  va_end(arg);
}

void call_test_3() { test_3("nonexist.ent/", (long long)42); }