unsigned short _Fract e1 = 0x1.e8p-1uhr; // CHECK-DAG: @e1 = {{.*}}global i8 -12
unsigned short _Fract e2 = 0x1.8ep-1uhr; // CHECK-DAG: @e2 = {{.*}}global i8 -57
unsigned short _Fract e3 = 0x1.ep-1uhr; //  CHECK-DAG: @e3 = {{.*}}global i8 -16
unsigned _Accum e4 = 0xep-1uk;    //  CHECK-DAG: @e4 = {{.*}}global i32 458752
unsigned _Accum e5 = 0xe.1p-1uk;  //  CHECK-DAG: @e5 = {{.*}}global i32 460800
unsigned _Accum e6 = 0xe.ep-1uk;  //  CHECK-DAG: @e6 = {{.*}}global i32 487424
unsigned _Accum e7 = 0xe.e8p-1uk; //  CHECK-DAG: @e7 = {{.*}}global i32 488448
unsigned _Accum e8 = 0xe.8ep-1uk; //  CHECK-DAG: @e8 = {{.*}}global i32 476928
unsigned short _Fract E1 = 0x1.E8p-1uhr; // CHECK-DAG: @E1 = {{.*}}global i8 -12
unsigned short _Fract E2 = 0x1.8Ep-1uhr; // CHECK-DAG: @E2 = {{.*}}global i8 -57
unsigned short _Fract E3 = 0x1.Ep-1uhr; //  CHECK-DAG: @E3 = {{.*}}global i8 -16
unsigned _Accum E4 = 0xEp-1uk;    //  CHECK-DAG: @E4 = {{.*}}global i32 458752
unsigned _Accum E5 = 0xE.1p-1uk;  //  CHECK-DAG: @E5 = {{.*}}global i32 460800
unsigned _Accum E6 = 0xE.Ep-1uk;  //  CHECK-DAG: @E6 = {{.*}}global i32 487424
unsigned _Accum E7 = 0xE.E8p-1uk; //  CHECK-DAG: @E7 = {{.*}}global i32 488448
unsigned _Accum E8 = 0xE.8Ep-1uk; //  CHECK-DAG: @E8 = {{.*}}global i32 476928