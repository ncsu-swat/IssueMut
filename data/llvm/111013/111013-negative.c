#include <stdbool.h>

void ignoreImplicitCastToBoolForComparisonResult() {
  bool boolFromComparison0 = (bool)(1 != 0);
  bool boolFromComparison1 = (bool)(1 == 0);
  bool boolFromComparison2 = (bool)(1 > 0);
  bool boolFromComparison3 = (bool)(1 >= 0);
  bool boolFromComparison4 = (bool)(1 < 0);
  bool boolFromComparison5 = (bool)(1 <= 0);
}