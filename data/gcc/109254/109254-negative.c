svfloat32_t func_demo_no_bug(svfloat32_t x, svfloat32_t y, svbool_t pg) {
  svfloat32_t z = svadd_f32_x(pg, x, svdup_f32(0x1.800fep19f));
  // Create a copy of pg before it's clobbered by the svcmplt instruction below.
  svbool_t pg_copy = svmov_z(svptrue_b32(), pg);
  svbool_t cmp = svcmplt_f32(pg, z, svdup_f32(0.0f));
  // Use the preserved copy of the predicate.
  svfloat32_t zM1 = svsub_f32_x(pg_copy, z, svdup_n_f32(1.0f));
  z = svsel_f32(cmp, zM1, z);
  svfloat32_t sum = svadd_f32_x(pg_copy, z, y);
  return sum;
}