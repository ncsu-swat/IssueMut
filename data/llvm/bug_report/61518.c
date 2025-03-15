
_Complex int valid2 = {1, 2}; // expected-warning {{complex integer}} \
                               //  expected-warning {{specifying real and imaginary components is an extension}}
// FIXME: We need some sort of warning for valid5
_Complex float valid5 = {1.0f,
                         1.0fi}; // expected-warning {{imaginary constants}} \
                                       // expected-warning {{specifying real and imaginary components is an extension}}
// initialization list
_Complex double cd = {
    1.0, 2.0,
    3.0}; // expected-warning {{specifying real and imaginary components is an extension}} \
                                     //  expected-warning {{excess elements in scalar initializer}}
_Complex float cf = {
    1.1f, 2.2f, 3.3f,
    4.4f}; // expected-warning {{specifying real and imaginary components is an extension}} \
                                             //  expected-warning {{excess elements in scalar initializer}}
