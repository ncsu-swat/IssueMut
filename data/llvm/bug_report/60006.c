#include <immintrin.h>

// Ensure _mm_test_all_ones macro doesn't reuse argument
__m128i expensive_call();
int pr60006() {
  // CHECK-LABEL: pr60006
  // CHECK: call {{.*}} @expensive_call
  // CHECK-NOT: call {{.*}} @expensive_call
  // CHECK: call i32 @llvm.x86.sse41.ptestc(<2 x i64> %{{.*}}, <2 x i64>
  // %{{.*}})
  return _mm_test_all_ones(expensive_call());
}
