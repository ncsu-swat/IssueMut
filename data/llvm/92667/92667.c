// RUN: %clang_cc1 -verify -std=c2x %s

// Ensure restrict is stripped
extern int *restrict p1;
extern int *p2;
extern typeof(p1) p1;
extern typeof_unqual(p1) p2;

// Ensure array qualifications are removed
extern const int aci[2];
extern const int acii[2][2];
extern int ai[2];
extern int aii[2][2];
extern typeof(aci) aci;
extern typeof_unqual(aci) ai;
extern typeof(acii) acii;
extern typeof_unqual(acii) aii;

extern int *restrict arpi[2];
extern int *restrict arpii[2][2];
extern int *api[2];
extern int *apii[2][2];
extern typeof(arpi) arpi;
extern typeof_unqual(arpi) api;
extern typeof(arpii) arpii;
extern typeof_unqual(arpii) apii;
