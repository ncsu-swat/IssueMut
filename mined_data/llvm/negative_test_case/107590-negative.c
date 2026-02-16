enum WithFwdDeclInconsistent : int;

enum WithFwdDeclInconsistent : int {

  EFI0 = 0,

  EFI1 = 1,
  EFI2 = 2,

};

enum WithFwdDeclZeroFirst : int;

enum WithFwdDeclZeroFirst : int {

  EFZ0 = 0,

  EFZ1,
  EFZ2,
};

enum WithFwdDeclSequential : int;

enum WithFwdDeclSequential : int {

  EFS0 = 2,

  EFS1 = 3,

  EFS2 = 4,

};