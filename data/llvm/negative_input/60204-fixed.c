void escapeChar(void) {
  asm("_foo:");
  
  
  
  asm("%%~call _foo" ::);
  
  
  
  asm("%%~jmp _foo" ::);
  
  
  
  asm("%%!icall" ::);
  
  
  
  asm("%%!ijmp" ::);
}