struct SlotIndex {
  int lie;
};
SlotIndex si7, si8;

unsigned u9, u6;
bool b3, b4;

unsigned getValue() {
  if (b4) {
    return u6;
  }
  return u9;
}

void transferValues() {
  unsigned RegIdx;
  SlotIndex End;
  RegIdx = getValue();
  End = b3 ? si7 : si8;
}