[[nodiscard]] int f3();

void GH104391() {
#define M (void)f3()
  M; 
     
}