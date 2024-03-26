#ifndef __DIFFTEST_H__
#define __DIFFTEST_H__


#include "../include/common.h"
#include "../include/debug.h"
#include "../include/macro.h"
#include "../include/utils.h"
#include "../include/paddr.h"


enum{ DIFFTEST_TO_DUT, DIFFTEST_TO_REF };

typedef struct {
    word_t gpr[32];
    vaddr_t pc;
}CPU_state;

#endif
