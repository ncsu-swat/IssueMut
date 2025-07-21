struct S s, t, u;

void a(void) { __atomic_exchange(&s, &t, &u, 0); }