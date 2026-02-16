
inline int ISN(int c) { return ('0' <= c && c <= '9'); }

int isx(int c) { return (ISN(c) || ('A' <= c && c <= 'F')); }