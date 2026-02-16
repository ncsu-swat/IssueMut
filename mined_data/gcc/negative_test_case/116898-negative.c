_BitInt(127) a;
_BitInt(511) b;

void foo(_BitInt(31) c) {
  do {
    c %= b;
  again:
  } while (c);
  a /= 0; 
  c -= a;
  
}