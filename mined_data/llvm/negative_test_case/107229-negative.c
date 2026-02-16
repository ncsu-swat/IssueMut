void test2(unsigned char *vqp, unsigned char *vpp, vector unsigned char vc1,
           vector unsigned char vc2, unsigned char *resp) {
  __vector_quad vq = *((__vector_quad *)vqp);
  __vector_pair vp = *((__vector_pair *)vpp);
  __vector_pair res __attribute__((aligned(32)));
  __builtin_vsx_build_pair(&res, vc1, vc2);
  *((__vector_pair *)resp) = res;
}