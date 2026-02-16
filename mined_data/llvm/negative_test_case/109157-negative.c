#ifdef INTEL
asm("mov eax, 1");
void foo() { asm("mov eax, 2"); }
#else
asm("mov eax, 1");
void foo() { asm("mov eax, 2"); }
#endif