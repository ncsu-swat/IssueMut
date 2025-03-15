#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
void safe_snprintf(char *outstring, const size_t length, const char *format,
                   ... ) __attribute__((format(printf, 3, 4)));
void safe_snprintf(char *outstring, const size_t length, const char *format,
                   ... ) __attribute__((format(printf, 3, 4))) {
  va_list args;
  va_start(args, format);
  if ((outstring != NULL) && (length > 0)) {
    vsnprintf(outstring, length, format, args);
    outstring[length - 1] = 0;
  }
  va_end(args);
}