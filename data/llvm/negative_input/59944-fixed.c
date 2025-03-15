extern int omp_get_initial_device();
extern void *omp_get_mapped_ptr(void *, int);

int x;

void t() { omp_get_mapped_ptr(&x, omp_get_initial_device()); }