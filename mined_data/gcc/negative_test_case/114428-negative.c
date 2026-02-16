void foo2(char *__restrict a, short *b) {
  for (int i = 0; i != 32; i++)
    a[i] = ((unsigned short)b[i]) >> 8;
}

void foo3(char *__restrict a, short *b) {
  for (int i = 0; i != 16; i++)
    a[i] = ((unsigned short)b[i]) >> 8;
}