typedef _Float16 v4hf __attribute__((vector_size(8)));
typedef _Float16 v2hf __attribute__((vector_size(4)));

v4hf foo(v4hf a, v4hf b) {
  a[0] = a[0] + b[0];
  a[1] = a[1] + b[1];
  a[2] = a[2] + b[2];
  a[3] = a[3] + b[3];
  return a;
}

v4hf foo2(v4hf a, v4hf b) {
  a[0] = a[0] - b[0];
  a[1] = a[1] - b[1];
  a[2] = a[2] - b[2];
  a[3] = a[3] - b[3];
  return a;
}

v4hf foo3(v4hf a, v4hf b) {
  a[0] = a[0] * b[0];
  a[1] = a[1] * b[1];
  a[2] = a[2] * b[2];
  a[3] = a[3] * b[3];
  return a;
}

v4hf foo1(v4hf a, v4hf b) {
  a[0] = a[0] / b[0];
  a[1] = a[1] / b[1];
  a[2] = a[2] / b[2];
  a[3] = a[3] / b[3];
  return a;
}

v2hf foo4(v2hf a, v2hf b) {
  a[0] = a[0] + b[0];
  a[1] = a[1] + b[1];
  return a;
}

v2hf foo5(v2hf a, v2hf b) {
  a[0] = a[0] - b[0];
  a[1] = a[1] - b[1];
  return a;
}

v2hf foo6(v2hf a, v2hf b) {
  a[0] = a[0] * b[0];
  a[1] = a[1] * b[1];
  return a;
}

v2hf foo7(v2hf a, v2hf b) {
  a[0] = a[0] / b[0];
  a[1] = a[1] / b[1];
  return a;
}