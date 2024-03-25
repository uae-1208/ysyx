#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define PMEM_SIZE 0x8000000
#define PMEM_BASE 0x80000000
#define PG_ALIGN __attribute((aligned(4096)))

#define paddr_t   uint32_t
#define word_t    uint32_t
#define vaddr_t   word_t

// npc trap
#define HIT_TRAP  1
#define ABORT     2

// calculate the length of an array
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))

// trace
#define CONFIG_ITRACE   1
#define CONFIG_FTRACE   1
#define CONFIG_IRINGBUF 1
#define MAX_iringbuf_size  20


#endif
