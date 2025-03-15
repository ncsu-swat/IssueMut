int d;

int main() {
  int temp = (d == 1 | d > 9);
  short shortened = (short)temp;
  d = shortened / 0;
}