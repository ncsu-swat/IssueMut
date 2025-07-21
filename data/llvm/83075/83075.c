// CHECK-LABEL: define{{.*}} void @test_builtin_clzg
void test_builtin_clzg(unsigned char uc, unsigned short us, unsigned int ui,
                       unsigned long ul, unsigned long long ull,
                       unsigned __int128 ui128, unsigned _BitInt(128) ubi128,
                       signed char sc, short s, int i) {
  volatile int lz;
  lz = __builtin_clzg(uc);
  // CHECK: %1 = load i8, ptr %uc.addr, align 1
  // CHECK-NEXT: %2 = call i8 @llvm.ctlz.i8(i8 %1, i1 true)
  // CHECK-NEXT: %cast = sext i8 %2 to i32
  // CHECK-NEXT: store volatile i32 %cast, ptr %lz, align 4
  lz = __builtin_clzg(us);
  // CHECK-NEXT: %3 = load i16, ptr %us.addr, align 2
  // CHECK-NEXT: %4 = call i16 @llvm.ctlz.i16(i16 %3, i1 true)
  // CHECK-NEXT: %cast1 = sext i16 %4 to i32
  // CHECK-NEXT: store volatile i32 %cast1, ptr %lz, align 4
  lz = __builtin_clzg(ui);
  // CHECK-NEXT: %5 = load i32, ptr %ui.addr, align 4
  // CHECK-NEXT: %6 = call i32 @llvm.ctlz.i32(i32 %5, i1 true)
  // CHECK-NEXT: store volatile i32 %6, ptr %lz, align 4
  lz = __builtin_clzg(ul);
  // CHECK-NEXT: %7 = load i64, ptr %ul.addr, align 8
  // CHECK-NEXT: %8 = call i64 @llvm.ctlz.i64(i64 %7, i1 true)
  // CHECK-NEXT: %cast2 = trunc i64 %8 to i32
  // CHECK-NEXT: store volatile i32 %cast2, ptr %lz, align 4
  lz = __builtin_clzg(ull);
  // CHECK-NEXT: %9 = load i64, ptr %ull.addr, align 8
  // CHECK-NEXT: %10 = call i64 @llvm.ctlz.i64(i64 %9, i1 true)
  // CHECK-NEXT: %cast3 = trunc i64 %10 to i32
  // CHECK-NEXT: store volatile i32 %cast3, ptr %lz, align 4
  lz = __builtin_clzg(ui128);
  // CHECK-NEXT: %11 = load i128, ptr %ui128.addr, align 16
  // CHECK-NEXT: %12 = call i128 @llvm.ctlz.i128(i128 %11, i1 true)
  // CHECK-NEXT: %cast4 = trunc i128 %12 to i32
  // CHECK-NEXT: store volatile i32 %cast4, ptr %lz, align 4
  lz = __builtin_clzg(ubi128);
  // CHECK-NEXT: %13 = load i128, ptr %ubi128.addr, align 8
  // CHECK-NEXT: %14 = call i128 @llvm.ctlz.i128(i128 %13, i1 true)
  // CHECK-NEXT: %cast5 = trunc i128 %14 to i32
  // CHECK-NEXT: store volatile i32 %cast5, ptr %lz, align 4
  lz = __builtin_clzg(uc, sc);
  // CHECK-NEXT: %15 = load i8, ptr %uc.addr, align 1
  // CHECK-NEXT: %16 = call i8 @llvm.ctlz.i8(i8 %15, i1 true)
  // CHECK-NEXT: %cast6 = sext i8 %16 to i32
  // CHECK-NEXT: %iszero = icmp eq i8 %15, 0
  // CHECK-NEXT: %17 = load i8, ptr %sc.addr, align 1
  // CHECK-NEXT: %conv = sext i8 %17 to i32
  // CHECK-NEXT: %clzg = select i1 %iszero, i32 %conv, i32 %cast6
  // CHECK-NEXT: store volatile i32 %clzg, ptr %lz, align 4
  lz = __builtin_clzg(us, uc);
  // CHECK-NEXT: %18 = load i16, ptr %us.addr, align 2
  // CHECK-NEXT: %19 = call i16 @llvm.ctlz.i16(i16 %18, i1 true)
  // CHECK-NEXT: %cast7 = sext i16 %19 to i32
  // CHECK-NEXT: %iszero8 = icmp eq i16 %18, 0
  // CHECK-NEXT: %20 = load i8, ptr %uc.addr, align 1
  // CHECK-NEXT: %conv9 = zext i8 %20 to i32
  // CHECK-NEXT: %clzg10 = select i1 %iszero8, i32 %conv9, i32 %cast7
  // CHECK-NEXT: store volatile i32 %clzg10, ptr %lz, align 4
  lz = __builtin_clzg(ui, s);
  // CHECK-NEXT: %21 = load i32, ptr %ui.addr, align 4
  // CHECK-NEXT: %22 = call i32 @llvm.ctlz.i32(i32 %21, i1 true)
  // CHECK-NEXT: %iszero11 = icmp eq i32 %21, 0
  // CHECK-NEXT: %23 = load i16, ptr %s.addr, align 2
  // CHECK-NEXT: %conv12 = sext i16 %23 to i32
  // CHECK-NEXT: %clzg13 = select i1 %iszero11, i32 %conv12, i32 %22
  // CHECK-NEXT: store volatile i32 %clzg13, ptr %lz, align 4
  lz = __builtin_clzg(ul, us);
  // CHECK-NEXT: %24 = load i64, ptr %ul.addr, align 8
  // CHECK-NEXT: %25 = call i64 @llvm.ctlz.i64(i64 %24, i1 true)
  // CHECK-NEXT: %cast14 = trunc i64 %25 to i32
  // CHECK-NEXT: %iszero15 = icmp eq i64 %24, 0
  // CHECK-NEXT: %26 = load i16, ptr %us.addr, align 2
  // CHECK-NEXT: %conv16 = zext i16 %26 to i32
  // CHECK-NEXT: %clzg17 = select i1 %iszero15, i32 %conv16, i32 %cast14
  // CHECK-NEXT: store volatile i32 %clzg17, ptr %lz, align 4
  lz = __builtin_clzg(ull, i);
  // CHECK-NEXT: %27 = load i64, ptr %ull.addr, align 8
  // CHECK-NEXT: %28 = call i64 @llvm.ctlz.i64(i64 %27, i1 true)
  // CHECK-NEXT: %cast18 = trunc i64 %28 to i32
  // CHECK-NEXT: %iszero19 = icmp eq i64 %27, 0
  // CHECK-NEXT: %29 = load i32, ptr %i.addr, align 4
  // CHECK-NEXT: %clzg20 = select i1 %iszero19, i32 %29, i32 %cast18
  // CHECK-NEXT: store volatile i32 %clzg20, ptr %lz, align 4
  lz = __builtin_clzg(ui128, i);
  // CHECK-NEXT: %30 = load i128, ptr %ui128.addr, align 16
  // CHECK-NEXT: %31 = call i128 @llvm.ctlz.i128(i128 %30, i1 true)
  // CHECK-NEXT: %cast21 = trunc i128 %31 to i32
  // CHECK-NEXT: %iszero22 = icmp eq i128 %30, 0
  // CHECK-NEXT: %32 = load i32, ptr %i.addr, align 4
  // CHECK-NEXT: %clzg23 = select i1 %iszero22, i32 %32, i32 %cast21
  // CHECK-NEXT: store volatile i32 %clzg23, ptr %lz, align 4
  lz = __builtin_clzg(ubi128, i);
  // CHECK-NEXT: %33 = load i128, ptr %ubi128.addr, align 8
  // CHECK-NEXT: %34 = call i128 @llvm.ctlz.i128(i128 %33, i1 true)
  // CHECK-NEXT: %cast24 = trunc i128 %34 to i32
  // CHECK-NEXT: %iszero25 = icmp eq i128 %33, 0
  // CHECK-NEXT: %35 = load i32, ptr %i.addr, align 4
  // CHECK-NEXT: %clzg26 = select i1 %iszero25, i32 %35, i32 %cast24
  // CHECK-NEXT: store volatile i32 %clzg26, ptr %lz, align 4
  // CHECK-NEXT: ret void
}
