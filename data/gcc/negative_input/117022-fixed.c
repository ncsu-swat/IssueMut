void foo(int w) {
  for (int x = 0; x < 32; ++x) {
    if (x == 0)
      continue;
    else if (x == 1)
      continue;
    else if (x == 2)
      continue;
    else if (x == 31)
      break;
  }
  int y = 0;
#pragma GCC unroll 2
  while (y < 16) {
    ++y;
    if (y == 12)
      continue;
    else if (y == 13)
      continue;
    else if (y == 14)
      break;
  }
  switch (y) {
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  }
  for (int x = 0; x < 2; ++x)
    switch (x) {
    case 0:
    case 3:
      for (int y = 0; y < 2; ++y)
        for (int z = 0; z < 2; ++z)
          for (int a = 0; a < 2; ++a)
            switch (a) {
            case 0:
              if (w == 0)
                break;
              else if (w == 1)
                break;
              else if (w == 2)
                break;
              else if (w == 3)
                break;
              else if (w == 4)
                break;
              else if (w == 5)
                break;
              else if (w == 6)
                break;
              else if (w == 7)
                continue;
              else if (w == 8)
                continue;
              else if (w == 9)
                continue;
              else if (w == 10)
                continue;
              do {
                if (w == 11)
                  break;
                else
                  continue;
              } while (0);
              break;
            default:
              break;
            }
      break;
    default:
      break;
    }
  for (int x = 0; x < 32; ++x)
    if (x == 31)
      break;
    else if (x == 30)
      break;
    else if (x == 29)
      continue;
  do {
    if (w == 42)
      continue;
    else if (w == 41)
      break;
  } while (1);
  while (w) {
    if (w == 40)
      break;
    else if (w == 39)
      continue;
  }
  switch (w) {
  case 42:
    break;
  default:
    break;
  }
}