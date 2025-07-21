
#define ISN(c) ('0' <= (c) && (c) <= '9')

int isx(int c) { return (ISN(c) || ('A' <= c && c <= 'F')); }