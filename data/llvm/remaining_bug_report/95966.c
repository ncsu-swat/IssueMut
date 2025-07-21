typedef float float4 __attribute__((ext_vector_type(4)));

void test_builtin_elementwise_tanh(float f1, float f2, double d1, double d2,
                                   float4 vf1, float4 vf2) {
  // CHECK-LABEL: define void @test_builtin_elementwise_tanh(
  // CHECK:      [[F1:%.+]] = load float, ptr %f1.addr, align 4
  // CHECK-NEXT:  call float @llvm.tanh.f32(float [[F1]])
  f2 = __builtin_elementwise_tanh(f1);

  // CHECK:      [[D1:%.+]] = load double, ptr %d1.addr, align 8
  // CHECK-NEXT: call double @llvm.tanh.f64(double [[D1]])
  d2 = __builtin_elementwise_tanh(d1);

  // CHECK:      [[VF1:%.+]] = load <4 x float>, ptr %vf1.addr, align 16
  // CHECK-NEXT: call <4 x float> @llvm.tanh.v4f32(<4 x float> [[VF1]])
  vf2 = __builtin_elementwise_tanh(vf1);
}

float4 strict_elementwise_tanh(float4 a) {
  return __builtin_elementwise_tanh(a);
}
