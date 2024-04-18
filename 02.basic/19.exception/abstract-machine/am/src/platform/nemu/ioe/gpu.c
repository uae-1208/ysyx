#include <am.h>
#include <nemu.h>
#include <stdio.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

#define Width  400 
#define Height 300 

void __am_gpu_init() 
{
  // int i;
  // int size_reg_value = inl(VGACTL_ADDR);  
  // int w = size_reg_value >> 16;
  // int h = size_reg_value & 0xffff; 
  // uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  // for (i = 0; i < w * h; i ++) 
  //   fb[i] = i;
  // outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) 
{
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    // .width = 0, .height = 0,
    .width = Width, .height = Height,
    .vmemsz = Width * Height
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) 
{
  int i, j;
  int pix_count = 0;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;

  if(ctl->w == 0 && ctl->h == 0)
    return ;
  
  //以一个块为单位进行填充
  for (j = 0; j < ctl->h; j++) 
    for (i = 0; i < ctl->w; i++) 
    {
      fb[(ctl->y + j) * Width + ctl->x + i] = ((uint32_t *)(ctl->pixels))[pix_count];
      pix_count++;
    }

  if (ctl->sync) 
    outl(SYNC_ADDR, 1);  
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
