int g_66, g_80_2;
void func_1func_41(int p_43) {
  do {
    g_80_2 = 0;
    while (g_80_2 <= 7) {
      g_66 = 0;
      while (g_66 <= 7) {
        if (p_43) {
          g_80_2 = 0;
          break;
        }
        g_66 += 1;
      }
      if (p_43) {
        continue;
      }
      g_80_2 += 1;
    }
  } while (p_43);
}