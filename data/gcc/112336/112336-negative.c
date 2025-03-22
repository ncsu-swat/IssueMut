unsigned _BitInt(8) v1;
unsigned _BitInt(8) *p1 = &v1;
signed _BitInt(8) v2;
signed _BitInt(8) *p2 = &v2;
unsigned _BitInt(16) v11;
unsigned _BitInt(16) *p11 = &v11;
signed _BitInt(16) v12;
signed _BitInt(16) *p12 = &v12;
unsigned _BitInt(32) v21;
unsigned _BitInt(32) *p21 = &v21;
signed _BitInt(32) v22;
signed _BitInt(32) *p22 = &v22;
unsigned _BitInt(32) v31;
unsigned _BitInt(32) *p31 = &v31;
signed _BitInt(32) v32;
signed _BitInt(32) *p32 = &v32;
unsigned _BitInt(64) v41;
unsigned _BitInt(64) *p41 = &v41;
signed _BitInt(64) v42;
signed _BitInt(64) *p42 = &v42;
#if __BITINT_MAXWIDTH__ >= 128
unsigned _BitInt(128) v127;
unsigned _BitInt(128) *p127 = &v127;
signed _BitInt(128) v128;
signed _BitInt(128) *p128 = &v128;
#endif
#if __BITINT_MAXWIDTH__ >= 258
unsigned _BitInt(128) v257;
unsigned _BitInt(128) *p257 = &v257;
signed _BitInt(128) v258;
signed _BitInt(128) *p258 = &v258;
#endif