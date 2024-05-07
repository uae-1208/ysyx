#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define PMEM_SIZE   0x8000000
#define PMEM_BASE   0x80000000
#define PG_ALIGN    __attribute((aligned(4096)))


#define paddr_t   uint32_t
#define word_t    uint32_t
#define vaddr_t   word_t

// npc trap
#define HIT_TRAP  1
#define ABORT     2
#define Unit_IDU1     0  
#define Unit_IDU2     1   
#define Unit_IDU3     2  
#define Unit_IDU4     3   
#define Unit_IDU5     4   
#define Unit_IDU6     5   
#define Unit_IDU7     6   
#define Unit_IDU8     7   
#define Unit_IDU9     8   
#define Unit_EXU1     9   
#define Unit_LSU1     10  
#define Unit_LSU2     11  
#define Unit_CC1      12 
#define Unit_CC2      13

// npc mem wirte mask
#define WByte  0b00000001
#define WHalf  0b00000011
#define WWord  0b00001111


// calculate the length of an array
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))

// trace
#define CONFIG_ITRACE      1
// #define CONFIG_MTRACE      1
// #define CONFIG_FTRACE      1
// #define CONFIG_ETRACE      1
#define CONFIG_IRINGBUF    1
#define CONFIG_DIFFTEST    1
#define MAX_iringbuf_size  20
#define CONFIG_WAVES       1


// device 
#define CONFIG_DEVICE        1
#define CONFIG_SERIAL_MMIO   0xa00003f8
#define CONFIG_RTC_MMIO      0xa0000048


// CSR
#define MSTATUS 0
#define MTVEC   1
#define MEPC    2
#define MCAUSE  3

#endif
