int g_66, g_80_2;
void func_1func_41(int p_43) {
  int restart_flag;
  do {
    restart_flag = 0;
    g_80_2 = 0;
    for (; g_80_2 <= 7; g_80_2 += 1) {
      g_66 = 0;
      for (; g_66 <= 7; g_66 += 1)
        if (p_43) {
          restart_flag = 1;
          break;
        }
      if (restart_flag)
        break;
    }
  } while (restart_flag);
}