float g(void);
int c(float);
float f = 1.0f;

void match(void) {

  for (float x = 0.1f; x <= 1.0f; x += 0.1f) {
  }

  for (; f > 0; --f) {
  }

  for (float x = 0.0f; c(x); x = g()) {
  }

  for (int i = 0; i < 10 && f < 2.0f; i++) {
    f++;
  }
}

void not_match(void) {
  for (int i = 0; i < 10; i += 1.0f) {
  }
  for (int i = 0; i < 10; ++i) {
  }
  for (int i = 0; i < 10; ++i, f++) {
  }
  for (int i = 0; f < 10.f; ++i) {
  }
}