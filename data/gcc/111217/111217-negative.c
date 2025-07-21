static inline _Bool nand(_Bool a, _Bool b) { return !(a && b); }

_Bool f(int a, int b) { return (_Bool)a ^ (_Bool)b; }