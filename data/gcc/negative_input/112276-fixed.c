typedef unsigned short __attribute__((__vector_size__(4))) __v2hu;
typedef short __attribute__((__vector_size__(4))) __v2hi;

typedef unsigned short __attribute__((__vector_size__(8))) __v4hu;
typedef short __attribute__((__vector_size__(8))) __v4hi;

typedef _Float16 __attribute__((__vector_size__(4))) __v2hf;
typedef _Float16 __attribute__((__vector_size__(8))) __v4hf;

__v2hu au, bu;
__v2hi as, bs;
__v2hf af, bf;

__v4hu cu, du;
__v4hi cs, ds;
__v4hf cf, df;

__v2hf auf(__v2hu a, __v2hu b) { return (a > b) ? af : bf; }
__v2hf asf(__v2hi a, __v2hi b) { return (a > b) ? af : bf; }

__v4hf cuf(__v4hu c, __v4hu d) { return (c > d) ? cf : df; }
__v4hf csf(__v4hi c, __v4hi d) { return (c > d) ? cf : df; }

__v2hf auf_ne(__v2hu a, __v2hu b) { return (a != b) ? af : bf; }
__v2hf asf_ne(__v2hi a, __v2hi b) { return (a != b) ? af : bf; }

__v4hf cuf_ne(__v4hu c, __v4hu d) { return (c != d) ? cf : df; }
__v4hf csf_ne(__v4hi c, __v4hi d) { return (c != d) ? cf : df; }