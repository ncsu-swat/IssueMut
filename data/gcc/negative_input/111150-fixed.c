typedef int v4si __attribute((__vector_size__(4 * sizeof(int))));

v4si f1_(v4si a, v4si b, v4si c, v4si d, v4si e, v4si f) {
  v4si mask1 = a == b;
  v4si X = (mask1 & e) | (~mask1 & f);
  v4si mask2 = c == d;
  v4si Y = (mask2 & e) | (~mask2 & f);
  return X != Y;
}

v4si f2_(v4si a, v4si b, v4si c, v4si d, v4si e, v4si f) {
  v4si mask1 = a == b;
  v4si X = (mask1 & e) | (~mask1 & f);
  v4si mask2 = c == d;
  v4si Y = (mask2 & e) | (~mask2 & f);
  return X == Y;
}

v4si f3_(v4si a, v4si b, v4si c, v4si d, v4si e, v4si f) {
  v4si mask1 = a == b;
  v4si X = (mask1 & e) | (~mask1 & f);
  v4si mask2 = c == d;
  v4si Y = (mask2 & f) | (~mask2 & e);
  return X != Y;
}

v4si f4_(v4si a, v4si b, v4si c, v4si d, v4si e, v4si f) {
  v4si mask1 = a == b;
  v4si X = (mask1 & e) | (~mask1 & f);
  v4si mask2 = c == d;
  v4si Y = (mask2 & f) | (~mask2 & e);
  return X == Y;
}