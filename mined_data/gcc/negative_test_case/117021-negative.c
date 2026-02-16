enum E { F = 10, G = 20 };

void foo(unsigned x) {
  switch (x) {
  case 1:
    break;
  case 0:
    break;
  default:
    break;
  }
}

void bar(unsigned x) {
  switch (x) {
  case 1 ... 2:


    break;
  case 3 ... 4:


    break;
  case 70 ... 70:
    break;
  case 78 ... 79:

    break;
  case 5 ... 5:

    break;
  case 6 ... 6:


    break;
  default:
    break;
  }
}

void baz(unsigned char x) {
  switch (x) {
  case 30 ... 32:

    break;
  case 33:
    break;
  case 42:
    break;
  case 40 ... 41:

    break;
  default:
    break;
  }
}

void qux(int x) {
  switch (x) {
  case -9 ... -9:

    break;
  case -6:
    break;
  case -7:
    break;
  case -8:
    break;
  case F ... G:
    break;
  case -10:
    break;
  case -11 ... -11:

    break;
  case -15 ... -15:

    break;
  case -16 ... -16:

    break;
  default:
    break;
  }
}