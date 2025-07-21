
// gh107590
enum WithFwdDeclInconsistent : int;

enum WithFwdDeclInconsistent : int {
  // CHECK-MESSAGES: :[[@LINE-1]]:1: warning: initial values in enum
  // 'WithFwdDeclInconsistent' are not consistent
  // CHECK-MESSAGES-ENABLE: :[[@LINE-2]]:1: warning: initial values in enum
  // 'WithFwdDeclInconsistent' are not consistent
  EFI0,
  // CHECK-FIXES: EFI0 = 0,
  EFI1 = 1,
  EFI2,
  // CHECK-FIXES: EFI2 = 2,
};

enum WithFwdDeclZeroFirst : int;

enum WithFwdDeclZeroFirst : int {
  // CHECK-MESSAGES-ENABLE: :[[@LINE+1]]:3: warning: zero initial value for the
  // first enumerator in 'WithFwdDeclZeroFirst' can be disregarded
  EFZ0 = 0,
  // CHECK-FIXES-ENABLE: EFZ0 ,
  EFZ1,
  EFZ2,
};

enum WithFwdDeclSequential : int;

enum WithFwdDeclSequential : int {
  // CHECK-MESSAGES-ENABLE: :[[@LINE-1]]:1: warning: sequential initial value in
  // 'WithFwdDeclSequential' can be ignored
  EFS0 = 2,
  // CHECK-FIXES-ENABLE: EFS0 = 2,
  EFS1 = 3,
  // CHECK-FIXES-ENABLE: EFS1 ,
  EFS2 = 4,
  // CHECK-FIXES-ENABLE: EFS2 ,
};
