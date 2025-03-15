#ifdef __AVR_TINY__
int func(char c)
#else
int func(char c)
#endif
{
  return c;
}