// RUN: %clang_cc1 %s -triple i386-unknown-unknown -Wno-strict-prototypes
// -emit-llvm -o - -verify | FileCheck %s

// PR88917: don't crash
int b();

int main() {
  return b(b);
  // CHECK: call i32 @b(ptr noundef @b)
}
int b(int (*f)()) { return 0; }
// CHECK-LABEL: define{{.*}} i32 @b(ptr noundef %f)
