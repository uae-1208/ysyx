#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) 
{ 
  kbd->keycode = inl(KBD_ADDR);
  if(kbd->keycode == AM_KEY_NONE)
  {
    kbd->keydown = 0;
    return;
  }

  // in send_key() in nemu
  // " uint32_t am_scancode = keymap[scancode] | (is_keydown ? KEYDOWN_MASK : 0); "
  if((kbd->keycode & KEYDOWN_MASK) == 0x8000)
  {
    kbd->keydown = 1;
    kbd->keycode = kbd->keycode & (~KEYDOWN_MASK);
  }
  else
    kbd->keydown = 0;
}
