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
    /* CSR */
    word_t csr[4];
    // 0x300 -> 0.mstatus;
    // 0x305 -> 1.mtvec;
    // 0x341 -> 2.mepc;
    // 0x342 -> 3.mcause;
}CPU_state;

#endif
