// CHECK-LE-LABEL: @test2(
// CHECK-LE-NEXT:  entry:
// CHECK-LE-NEXT:    [[TMP0:%.*]] = tail call <256 x i1>
// @llvm.ppc.vsx.assemble.pair(<16 x i8> [[VC2:%.*]], <16 x i8> [[VC1:%.*]])
// CHECK-LE-NEXT:    store <256 x i1> [[TMP0]], ptr [[RESP:%.*]], align 32,
// !tbaa [[TBAA6:![0-9]+]] CHECK-LE-NEXT:    ret void
//
// CHECK-BE-LABEL: @test2(
// CHECK-BE-NEXT:  entry:
// CHECK-BE-NEXT:    [[TMP0:%.*]] = tail call <256 x i1>
// @llvm.ppc.vsx.assemble.pair(<16 x i8> [[VC1:%.*]], <16 x i8> [[VC2:%.*]])
// CHECK-BE-NEXT:    store <256 x i1> [[TMP0]], ptr [[RESP:%.*]], align 32,
// !tbaa [[TBAA6:![0-9]+]] CHECK-BE-NEXT:    ret void
//
// CHECK-LE-NOOPT-LABEL: @test2(
// CHECK-LE-NOOPT-NEXT:  entry:
// CHECK-LE-NOOPT-NEXT:    [[VQP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VPP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VC1_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[VC2_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[RESP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VQ:%.*]] = alloca <512 x i1>, align 64
// CHECK-LE-NOOPT-NEXT:    [[VP:%.*]] = alloca <256 x i1>, align 32
// CHECK-LE-NOOPT-NEXT:    [[RES:%.*]] = alloca <256 x i1>, align 32
// CHECK-LE-NOOPT-NEXT:    store ptr [[VQP:%.*]], ptr [[VQP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store ptr [[VPP:%.*]], ptr [[VPP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC1:%.*]], ptr [[VC1_ADDR]], align
// 16 CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC2:%.*]], ptr [[VC2_ADDR]],
// align 16 CHECK-LE-NOOPT-NEXT:    store ptr [[RESP:%.*]], ptr [[RESP_ADDR]],
// align 8 CHECK-LE-NOOPT-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[VQP_ADDR]],
// align 8 CHECK-LE-NOOPT-NEXT:    [[TMP1:%.*]] = load <512 x i1>, ptr [[TMP0]],
// align 64 CHECK-LE-NOOPT-NEXT:    store <512 x i1> [[TMP1]], ptr [[VQ]], align
// 64 CHECK-LE-NOOPT-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[VPP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    [[TMP3:%.*]] = load <256 x i1>, ptr [[TMP2]], align
// 32 CHECK-LE-NOOPT-NEXT:    store <256 x i1> [[TMP3]], ptr [[VP]], align 32
// CHECK-LE-NOOPT-NEXT:    [[TMP4:%.*]] = load <16 x i8>, ptr [[VC1_ADDR]],
// align 16 CHECK-LE-NOOPT-NEXT:    [[TMP5:%.*]] = load <16 x i8>, ptr
// [[VC2_ADDR]], align 16 CHECK-LE-NOOPT-NEXT:    [[TMP6:%.*]] = call <256 x i1>
// @llvm.ppc.vsx.assemble.pair(<16 x i8> [[TMP5]], <16 x i8> [[TMP4]])
// CHECK-LE-NOOPT-NEXT:    store <256 x i1> [[TMP6]], ptr [[RES]], align 32
// CHECK-LE-NOOPT-NEXT:    [[TMP7:%.*]] = load <256 x i1>, ptr [[RES]], align 32
// CHECK-LE-NOOPT-NEXT:    [[TMP8:%.*]] = load ptr, ptr [[RESP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store <256 x i1> [[TMP7]], ptr [[TMP8]], align 32
// CHECK-LE-NOOPT-NEXT:    ret void
//
void test2(unsigned char *vqp, unsigned char *vpp, vector unsigned char vc1,
           vector unsigned char vc2, unsigned char *resp) {
  __vector_quad vq = *((__vector_quad *)vqp);
  __vector_pair vp = *((__vector_pair *)vpp);
  __vector_pair res;
  __builtin_vsx_build_pair(&res, vc1, vc2);
  *((__vector_pair *)resp) = res;
}
