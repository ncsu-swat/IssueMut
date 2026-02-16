int main() {
  static bool CONDITION = false;

  { static bool CONDITION = true; }
}