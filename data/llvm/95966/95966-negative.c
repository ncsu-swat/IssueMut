typedef float float4 __attribute__((ext_vector_type(4)));

void test_builtin_elementwise_tanh(float f1, float f2, double d1, double d2,
                                   float4 vf1, float4 vf2) {

  f2 = __builtin_elementwise_tanh(f1);

  d2 = tanh(d1);

  vf2 = __builtin_elementwise_tanh(vf1);
}

float4 strict_elementwise_tanh(float4 a) {
  return __builtin_elementwise_tanh(a);
}