#include <am.h>
#include <nemu.h>

extern char _heap_start;
int main(const char *args);

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

void malloc_reset();


//ebreak/hit good trap : code  = 0 
//hit bad trap  : code != 0
void halt(int code) {
  nemu_trap(code);
  // should not reach here
  while (1);
}

void _trm_init() {
  malloc_reset();
  int ret = main(mainargs);
  halt(ret);
}
