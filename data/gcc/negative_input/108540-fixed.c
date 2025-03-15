__attribute__((noipa)) void bar(const char *cp, unsigned long size, char sign,
                                int dsgn) {
  if (__builtin_strcmp(cp, "ZERO") != 0 || size != 4 || sign != '-' ||
      dsgn != 1)
    __builtin_abort();
}

__attribute__((noipa)) void foo(int x, int ch, double d) {
  const char *cp = "";
  unsigned long size = 0;
  char sign = '\0';
  volatile double vd = d; // Add volatile to prevent optimization
  switch (x) {
  case 42:
    if (__builtin_isinf(vd)) {
      if (vd < 0)
        sign = '-';
      cp = "Inf";
      size = 3;
      break;
    }
    if (__builtin_isnan(vd)) {
      cp = "NaN";
      size = 3;
      break;
    }
    if (vd < 0) {
      vd = -vd;
      sign = '-';
    } else if (vd == 0.0 && __builtin_signbit(vd))
      sign = '-';
    else
      sign = '\0';
    if (ch == 'a' || ch == 'A') {
      union U {
        long long l;
        double d;
      } u;
      int dsgn;
      u.d = vd;
      if (u.l < 0) {
        dsgn = 1;
        u.l &= 0x7fffffffffffffffLL;
      } else
        dsgn = 0;
      if (__builtin_isinf(vd)) {
        cp = "INF";
        size = 3;
      } else if (__builtin_isnan(vd)) {
        cp = "NAN";
        size = 3;
      } else if (vd == 0) {
        cp = "ZERO";
        size = 4;
      } else {
        cp = "WRONG";
        size = 5;
      }
      bar(cp, size, sign, dsgn);
    }
  }
}

int main() {
  foo(42, 'a', -0.0);
  return 0;
}