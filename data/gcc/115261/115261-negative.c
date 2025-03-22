typedef signed char v2qi __attribute__ ((vector_size (2)));
typedef short v2hi __attribute__ ((vector_size (4)));
typedef int v2si __attribute__ ((vector_size (8)));
typedef long long v2di __attribute__ ((vector_size (16)));

typedef unsigned char uv2qi __attribute__ ((vector_size (2)));
typedef unsigned short uv2hi __attribute__ ((vector_size (4)));
typedef unsigned int uv2si __attribute__ ((vector_size (8)));
typedef unsigned long long uv2di __attribute__ ((vector_size (16)));

v2hi extendv2qiv2hi2 (v2qi x)
{
  return __builtin_convertvector (x, v2hi);
}

v2si extendv2hiv2si2 (v2hi x)
{
  return __builtin_convertvector (x, v2si);
}

v2di extendv2siv2di2 (v2si x)
{
  return __builtin_convertvector (x, v2di);
}

uv2hi extenduv2qiuv2hi2 (uv2qi x)
{
  return __builtin_convertvector (x, uv2hi);
}

uv2si extenduv2hiuv2si2 (uv2hi x)
{
  return __builtin_convertvector (x, uv2si);
}

uv2di extenduv2siuv2di2 (uv2si x)
{
  return __builtin_convertvector (x, uv2di);
}

v2di combined_function(v2si a, v2si b) {
    v2di result;
    result = extendv2siv2di2(a) + extendv2siv2di2(b);
    return result;
}