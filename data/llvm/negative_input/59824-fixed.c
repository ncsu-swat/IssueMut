#include <stdarg.h>

void a(const char *a, ...) __attribute__((format(printf, 1, 2))); 

__attribute__((format(printf, 1, 2))) void
forward_fixed(const char *fmt, ...) { 
    va_list args;
    va_start(args, fmt);
    forward_fixed(fmt, args);
    a(fmt, args);
    va_end(args);
}