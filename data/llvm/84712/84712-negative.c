typedef enum EnumA { A } EnumA;

enum EnumB {
  B,
  B1 = 1,

  B2 = (int)A == (int)B1
};

enum { C };

void foo(void) {
  enum EnumA a = A;
  enum EnumB b = B;
  (int)A == (int)B;

  (int)a == (int)(B);

  (int)a == (int)b;

  (int)A > (int)B;

  (int)A >= (int)b;

  (int)a > (int)b;

  ((int)(A)) <= ((int)(B));

  (int)a < (int)B;

  (int)a < (int)b;

  (int)a == (int)C;
  (int)A < (int)C;
  (int)b >= (int)C;
}