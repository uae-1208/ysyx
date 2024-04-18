/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef __RISCV_REG_H__
#define __RISCV_REG_H__

#include <common.h>

static inline int check_reg_idx(int idx) {
  IFDEF(CONFIG_RT_CHECK, assert(idx >= 0 && idx < MUXDEF(CONFIG_RVE, 16, 32)));
  return idx;
}
#define gpr(idx) (cpu.gpr[check_reg_idx(idx)])


#define MSTATUS 0
#define MTVEC   1
#define MEPC    2
#define MCAUSE  3
static inline int csr_idx_map(int idx) {
  switch (idx){                                       
    case 0x300 : return MSTATUS;    break;   // mstatus          
    case 0x305 : return MTVEC;      break;   // mtvec          
    case 0x341 : return MEPC;       break;   // mepc          
    case 0x342 : return MCAUSE;     break;   // mcause          
    default    : assert(0); 
    // default    : Log("pc = 0x%08x", cpu.pc); assert(0); 
  }   
}
#define CSR(idx) (cpu.csr[csr_idx_map(idx)])

static inline const char* reg_name(int idx) {
  extern const char* regs[];
  return regs[check_reg_idx(idx)];
}

#endif
