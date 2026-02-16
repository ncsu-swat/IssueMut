typedef double sometype;

sometype get_elem(sometype __attribute__((vector_size(16))) v) { return v[0]; }