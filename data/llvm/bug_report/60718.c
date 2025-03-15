#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
void safe_snprintf(char *outstring, const size_t length, const char *format,
                   ... /* args */);
void safe_snprintf(char *outstring, const size_t length, const char *format,
                   ... /* args */) {
  va_list args;
  va_start(args, format);
  if ((outstring != NULL) && (length > 0)) {
    vsnprintf(outstring, length, format, args);
    outstring[length - 1] = 0;
  }
  va_end(args);
}