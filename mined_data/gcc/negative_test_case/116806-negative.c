#include <limits.h>

extern void abort(void);

int main() {
  
#if INT_MAX > 127
  int scale = (int)(unsigned char)-1 + 1;

  if ('ab' != (int)((unsigned char)'a' * (unsigned int)scale + (unsigned char)'b'))
    abort();

  if ('\234b' !=
      (int)((unsigned char)'\234' * (unsigned int)scale + (unsigned char)'b'))
    abort();

  if ('b\234' != (int)((unsigned char)'b' * (unsigned int)scale + (unsigned char)'\234'))
    abort();
    
#if INT_MAX == 32767
#if '\234a' > 0
#error Preprocessor charconsts 1
#endif
  if ('\234a' > 0)
    abort();
#elif INT_MAX == 2147483647
#if '\234aaa' > 0
#error Preprocessor charconsts 2
#endif
  if ('\234aaa' > 0)
    abort();
#elif INT_MAX == 9223372036854775807
#if '\234aaaaaaa' > 0
#error Preprocessor charconsts 3
#endif
  if ('\234aaaaaaa' > 0)
    abort();
#endif
#endif
  return 0;
}