typedef _Float16 v4hf __attribute__((vector_size(8)));
typedef _Float16 v2hf __attribute__((vector_size(4)));

v4hf foo(v4hf a, v4hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, 2, 3, -1, -1, -1, -1);
  v8hf tmp_b = __builtin_shufflevector(b, b, 0, 1, 2, 3, -1, -1, -1, -1);
  v8hf result = tmp_a + tmp_b;
  return __builtin_shufflevector(result, result, 0, 1, 2, 3);
}

v4hf foo2(v4hf a, v4hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, 2, 3, -1, -1, -1, -1);
  v8hf tmp_b = __builtin_shufflevector(b, b, 0, 1, 2, 3, -1, -1, -1, -1);
  v8hf result = tmp_a - tmp_b;
  return __builtin_shufflevector(result, result, 0, 1, 2, 3);
}

v4hf foo3(v4hf a, v4hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, 2, 3, -1, -1, -1, -1);
  v8hf tmp_b = __builtin_shufflevector(b, b, 0, 1, 2, 3, -1, -1, -1, -1);
  v8hf result = tmp_a * tmp_b;
  return __builtin_shufflevector(result, result, 0, 1, 2, 3);
}

v4hf foo1(v4hf a, v4hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, 2, 3, -1, -1, -1, -1);
  v8hf tmp_b = __builtin_shufflevector(b, b, 0, 1, 2, 3, 1.0, 1.0, 1.0, 1.0);
  v8hf result = tmp_a / tmp_b;
  return __builtin_shufflevector(result, result, 0, 1, 2, 3);
}

v2hf foo4(v2hf a, v2hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, -1, -1, -1, -1, -1, -1);
  v8hf tmp_b = __builtin_shufflevector(b, b, 0, 1, -1, -1, -1, -1, -1, -1);
  v8hf result = tmp_a + tmp_b;
  return __builtin_shufflevector(result, result, 0, 1);
}

v2hf foo5(v2hf a, v2hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, -1, -1, -1, -1, -1, -1);
  v8hf tmp_b = __builtin_shufflevector(b, b, 0, 1, -1, -1, -1, -1, -1, -1);
  v8hf result = tmp_a - tmp_b;
  return __builtin_shufflevector(result, result, 0, 1);
}

v2hf foo6(v2hf a, v2hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, -1, -1, -1, -1, -1, -1);
  v8hf tmp_b = __builtin_shufflevector(b, b, 0, 1, -1, -1, -1, -1, -1, -1);
  v8hf result = tmp_a * tmp_b;
  return __builtin_shufflevector(result, result, 0, 1);
}

v2hf foo7(v2hf a, v2hf b) {
  v8hf tmp_a = __builtin_shufflevector(a, a, 0, 1, -1, -1, -1, -1, -1, -1);
  v8hf tmp_b =
      __builtin_shufflevector(b, b, 0, 1, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
  v8hf result = tmp_a / tmp_b;
  return __builtin_shufflevector(result, result, 0, 1);
}