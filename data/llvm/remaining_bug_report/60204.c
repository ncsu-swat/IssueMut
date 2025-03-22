// REQUIRES: avr-registered-target
// RUN: %clang_cc1 -x c -triple avr -target-cpu at90s8515 -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes=CHECK,AVR25 %s
// RUN: %clang_cc1 -x c -triple avr -target-cpu atmega328 -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes=CHECK,AVR51 %s
// RUN: %clang_cc1 -x c -triple avr -target-cpu atmega2560 -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes=CHECK,AVR6 %s

void escapeChar(void) {
  asm("_foo:");
  // AVR25: call addrspace(0) void asm sideeffect "rcall _foo"
  // AVR51: call addrspace(0) void asm sideeffect "call _foo"
  // AVR6:  call addrspace(0) void asm sideeffect "call _foo"
  asm("%~call _foo" ::);
  // AVR25: call addrspace(0) void asm sideeffect "rjmp _foo"
  // AVR51: call addrspace(0) void asm sideeffect "jmp _foo"
  // AVR6:  call addrspace(0) void asm sideeffect "jmp _foo"
  asm("%~jmp _foo" ::);
  // AVR25: call addrspace(0) void asm sideeffect "icall"
  // AVR51: call addrspace(0) void asm sideeffect "icall"
  // AVR6:  call addrspace(0) void asm sideeffect "eicall"
  asm("%!icall" ::);
  // AVR25: call addrspace(0) void asm sideeffect "ijmp"
  // AVR51: call addrspace(0) void asm sideeffect "ijmp"
  // AVR6:  call addrspace(0) void asm sideeffect "eijmp"
  asm("%!ijmp" ::);
}
