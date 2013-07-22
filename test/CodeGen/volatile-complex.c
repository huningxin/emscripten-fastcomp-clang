// RUN: %clang_cc1 -triple x86_64-unknown-unknown -emit-llvm %s -o - | FileCheck %s

// Validate that volatile _Complex loads and stores are generated
// properly, including their alignment (even when overaligned).
//
// This test assumes that floats are 32-bit aligned and doubles are
// 64-bit aligned, and uses x86-64 as a target that should have this
// datalayout.

// CHECK: target datalayout = "{{.*}}f32:32:32-f64:64:64{{.*}}"

volatile _Complex float cf;
volatile _Complex double cd;
volatile _Complex float cf32 __attribute__((aligned(32)));
volatile _Complex double cd32 __attribute__((aligned(32)));


// CHECK: define void @test_cf()
// CHECK-NEXT: entry:
void test_cf() {
  // CHECK-NEXT: load volatile float* getelementptr inbounds ({ float, float }* @cf, i32 0, i32 0), align 4
  // CHECK-NEXT: load volatile float* getelementptr inbounds ({ float, float }* @cf, i32 0, i32 1), align 4
  (void)(cf);
  // CHECK-NEXT: [[R:%.*]] = load volatile float* getelementptr inbounds ({ float, float }* @cf, i32 0, i32 0), align 4
  // CHECK-NEXT: [[I:%.*]] = load volatile float* getelementptr inbounds ({ float, float }* @cf, i32 0, i32 1), align 4
  // CHECK-NEXT: store volatile float [[R]], float* getelementptr inbounds ({ float, float }* @cf, i32 0, i32 0), align 4
  // CHECK-NEXT: store volatile float [[I]], float* getelementptr inbounds ({ float, float }* @cf, i32 0, i32 1), align 4
  (void)(cf=cf);
  // CHECK-NEXT: ret void
}

// CHECK: define void @test_cd()
// CHECK-NEXT: entry:
void test_cd() {
  // CHECK-NEXT: load volatile double* getelementptr inbounds ({ double, double }* @cd, i32 0, i32 0), align 8
  // CHECK-NEXT: load volatile double* getelementptr inbounds ({ double, double }* @cd, i32 0, i32 1), align 8
  (void)(cd);
  // CHECK-NEXT: [[R:%.*]] = load volatile double* getelementptr inbounds ({ double, double }* @cd, i32 0, i32 0), align 8
  // CHECK-NEXT: [[I:%.*]] = load volatile double* getelementptr inbounds ({ double, double }* @cd, i32 0, i32 1), align 8
  // CHECK-NEXT: store volatile double [[R]], double* getelementptr inbounds ({ double, double }* @cd, i32 0, i32 0), align 8
  // CHECK-NEXT: store volatile double [[I]], double* getelementptr inbounds ({ double, double }* @cd, i32 0, i32 1), align 8
  (void)(cd=cd);
  // CHECK-NEXT: ret void
}

// CHECK: define void @test_cf32()
// CHECK-NEXT: entry:
void test_cf32() {
  // CHECK-NEXT: load volatile float* getelementptr inbounds ({ float, float }* @cf32, i32 0, i32 0), align 32
  // CHECK-NEXT: load volatile float* getelementptr inbounds ({ float, float }* @cf32, i32 0, i32 1), align 4
  (void)(cf32);
  // CHECK-NEXT: [[R:%.*]] = load volatile float* getelementptr inbounds ({ float, float }* @cf32, i32 0, i32 0), align 32
  // CHECK-NEXT: [[I:%.*]] = load volatile float* getelementptr inbounds ({ float, float }* @cf32, i32 0, i32 1), align 4
  // CHECK-NEXT: store volatile float [[R]], float* getelementptr inbounds ({ float, float }* @cf32, i32 0, i32 0), align 32
  // CHECK-NEXT: store volatile float [[I]], float* getelementptr inbounds ({ float, float }* @cf32, i32 0, i32 1), align 4
  (void)(cf32=cf32);
  // CHECK-NEXT: ret void
}

// CHECK: define void @test_cd32()
// CHECK-NEXT: entry:
void test_cd32() {
  // CHECK-NEXT: load volatile double* getelementptr inbounds ({ double, double }* @cd32, i32 0, i32 0), align 32
  // CHECK-NEXT: load volatile double* getelementptr inbounds ({ double, double }* @cd32, i32 0, i32 1), align 8
  (void)(cd32);
  // CHECK-NEXT: [[R:%.*]] = load volatile double* getelementptr inbounds ({ double, double }* @cd32, i32 0, i32 0), align 32
  // CHECK-NEXT: [[I:%.*]] = load volatile double* getelementptr inbounds ({ double, double }* @cd32, i32 0, i32 1), align 8
  // CHECK-NEXT: store volatile double [[R]], double* getelementptr inbounds ({ double, double }* @cd32, i32 0, i32 0), align 32
  // CHECK-NEXT: store volatile double [[I]], double* getelementptr inbounds ({ double, double }* @cd32, i32 0, i32 1), align 8
  (void)(cd32=cd32);
  // CHECK-NEXT: ret void
}
