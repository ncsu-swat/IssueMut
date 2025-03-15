#include <limits.h>
#include <stdint.h>

uint32_t f(void);

int32_t i3(void) { return (int32_t)f() <= INT32_MAX; }

int32_t i3a(void) { return (int32_t)f() < INT32_MAX; }

int32_t i3b(void) { return (int32_t)f() >= INT32_MIN; }

int32_t i3c(void) { return (int32_t)f() > INT32_MIN; }