enum E { F = 10, G = 20 };

void foo(unsigned x) {
  switch (x) {
  case -1:
    break;
  default:
    break;
  }
}

void bar(unsigned x) {
  switch (x) {
  case 70:
    break;
  case ~0U:
    break;
  default:
    break;
  }
}

void baz(unsigned char x) {
  switch (x) {
  case 224:
    break;
  case 225:
    break;
  case 214:
    break;
  default:
    break;
  }
}

void qux(int x) {
  switch (x) {
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
  default:
    break;
  }
}