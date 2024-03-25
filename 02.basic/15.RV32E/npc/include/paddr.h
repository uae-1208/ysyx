#ifndef _PADDR_H__
#define _PADDR_H__

#include "common.h"

#define PMEM_LEFT  ((paddr_t)PMEM_BASE)
#define PMEM_RIGHT ((paddr_t)PMEM_BASE + PMEM_SIZE - 1)
#define RESET_VECTOR PMEM_LEFT

#endif
