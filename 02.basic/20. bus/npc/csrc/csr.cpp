#include "../include/common.h"

#define top_mstatus   top->rv32__DOT__csr_ctrl_inst__DOT__mstatus
#define top_mtvec     top->rv32__DOT__csr_ctrl_inst__DOT__mtvec
#define top_mepc      top->rv32__DOT__csr_ctrl_inst__DOT__mepc
#define top_mcause    top->rv32__DOT__csr_ctrl_inst__DOT__mcause


// extern void etrace(int inst)
// {
//   _Log(ANSI_FG_YELLOW "[etrace]" ANSI_NONE ANSI_FG_YELLOW "mstatus:" ANSI_NONE "0x%08x, "
//        ANSI_FG_YELLOW "mepc:"    ANSI_NONE " 0x%08x, " ANSI_FG_YELLOW "mcause:" ANSI_NONE " 0x%08x\n", 
//       top_mstatus, top_mepc, top_mcause);
// }

