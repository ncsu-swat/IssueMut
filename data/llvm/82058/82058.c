#ifdef __x86_64__
void test_builtin_popcountg(unsigned char uc, unsigned short us,
                            unsigned int ui, unsigned long ul,
                            unsigned long long ull, unsigned __int128 ui128,
                            unsigned _BitInt(128) ubi128) {
  volatile int pop;
  pop = __builtin_popcountg(uc);
  // CHECK: %1 = load i8, ptr %uc.addr, align 1
  // CHECK-NEXT: %conv = zext i8 %1 to i32
  // CHECK-NEXT: %2 = call i32 @llvm.ctpop.i32(i32 %conv)
  // CHECK-NEXT: store volatile i32 %2, ptr %pop, align 4
  pop = __builtin_popcountg(us);
  // CHECK-NEXT: %3 = load i16, ptr %us.addr, align 2
  // CHECK-NEXT: %conv1 = zext i16 %3 to i32
  // CHECK-NEXT: %4 = call i32 @llvm.ctpop.i32(i32 %conv1)
  // CHECK-NEXT: store volatile i32 %4, ptr %pop, align 4
  pop = __builtin_popcountg(ui);
  // CHECK-NEXT: %5 = load i32, ptr %ui.addr, align 4
  // CHECK-NEXT: %6 = call i32 @llvm.ctpop.i32(i32 %5)
  // CHECK-NEXT: store volatile i32 %6, ptr %pop, align 4
  pop = __builtin_popcountg(ul);
  // CHECK-NEXT: %7 = load i64, ptr %ul.addr, align 8
  // CHECK-NEXT: %8 = call i64 @llvm.ctpop.i64(i64 %7)
  // CHECK-NEXT: %cast = trunc i64 %8 to i32
  // CHECK-NEXT: store volatile i32 %cast, ptr %pop, align 4
  pop = __builtin_popcountg(ull);
  // CHECK-NEXT: %9 = load i64, ptr %ull.addr, align 8
  // CHECK-NEXT: %10 = call i64 @llvm.ctpop.i64(i64 %9)
  // CHECK-NEXT: %cast2 = trunc i64 %10 to i32
  // CHECK-NEXT: store volatile i32 %cast2, ptr %pop, align 4
  pop = __builtin_popcountg(ui128);
  // CHECK-NEXT: %11 = load i128, ptr %ui128.addr, align 16
  // CHECK-NEXT: %12 = call i128 @llvm.ctpop.i128(i128 %11)
  // CHECK-NEXT: %cast3 = trunc i128 %12 to i32
  // CHECK-NEXT: store volatile i32 %cast3, ptr %pop, align 4
  pop = __builtin_popcountg(ubi128);
  // CHECK-NEXT: %13 = load i128, ptr %ubi128.addr, align 8
  // CHECK-NEXT: %14 = call i128 @llvm.ctpop.i128(i128 %13)
  // CHECK-NEXT: %cast4 = trunc i128 %14 to i32
  // CHECK-NEXT: store volatile i32 %cast4, ptr %pop, align 4
  // CHECK-NEXT: ret void
}

#endif

typedef int int2 __attribute__((ext_vector_type(2)));

void test_builtin_popcountg(int i, double d, int2 i2) {
  __builtin_popcountg();
  // expected-error@-1 {{too few arguments to function call, expected 1, have
  // 0}}
  __builtin_popcountg(i, i);
  // expected-error@-1 {{too many arguments to function call, expected 1, have
  // 2}}
  __builtin_popcountg(d);
  // expected-error@-1 {{1st argument must be a type of integer (was 'double')}}
  __builtin_popcountg(i2);
  // expected-error@-1 {{1st argument must be a type of integer (was 'int2'
  // (vector of 2 'int' values))}}
}