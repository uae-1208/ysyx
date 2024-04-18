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

#include <isa.h>
#include "local-include/reg.h"
#include "utils.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() 
{
  _Log(ANSI_FG_RED "RegName  Hex_Value       Dec_Value\n" ANSI_NONE);
  _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\n", "pc", cpu.pc, cpu.pc);
  for(int i = 0; i < 32; i++)
  {
    _Log(ANSI_FG_YELLOW "$%s\t " ANSI_NONE, regs[i]);
    _Log("0x%08x\t %010u\n", cpu.gpr[i], cpu.gpr[i]);
  }
}

void isa_single_reg_display(char *reg_name) 
{
  int i;
  //pc
  _Log(ANSI_FG_RED "RegName  Hex_Value       U-Dec_Value       Dec_Value\n\33[0m");
  if(strcmp(reg_name, "pc") == 0)
  {
    _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u %010d\n", "pc", cpu.pc, cpu.pc, cpu.pc);
    return;
  }

  //reg $0
  if(strcmp(reg_name, regs[0]) == 0)
  {
    _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "$0", cpu.gpr[1], cpu.gpr[1], cpu.gpr[1]);
    return;
  }      

  //gpr
  for(i = 1; i < 32; i++)
    if(strcmp(reg_name, regs[i]) == 0)
    {
      _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", regs[i], cpu.gpr[i], cpu.gpr[i], cpu.gpr[i]);
      return;
    }

  // mstatus
  if(strcmp(reg_name, "mstatus") == 0)
  {
    _Log(ANSI_FG_YELLOW "$%s" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mstatus", 
         cpu.csr[MSTATUS], cpu.csr[MSTATUS], cpu.csr[MSTATUS]);
    return;
  }
  // mtvec;
  if(strcmp(reg_name, "mtvec") == 0)
  {
    _Log(ANSI_FG_YELLOW "$%s"     ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mtvec", 
         cpu.csr[MTVEC], cpu.csr[MTVEC], cpu.csr[MTVEC]);
    return;
  }
  // mepc;
  if(strcmp(reg_name, "mepc") == 0)
  {
    _Log(ANSI_FG_YELLOW "$%s"      ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mepc", 
         cpu.csr[MEPC], cpu.csr[MEPC], cpu.csr[MEPC]);
    return;
  }
  // mcause;
  if(strcmp(reg_name, "mcause") == 0)
  {
    _Log(ANSI_FG_YELLOW "$%s " ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mcause", 
         cpu.csr[MCAUSE], cpu.csr[MCAUSE], cpu.csr[MCAUSE]);
    return;
  }

  Warn("No register %s.", reg_name);
}

word_t isa_reg_str2val(const char *s, bool *success) 
{
  int i;
  //pc
  if(strcmp(s, "pc") == 0)
      return cpu.pc; 
      
  //reg $0
  if(strcmp(s, regs[0]) == 0)
      return cpu.gpr[0];
      
  //others
  for(i = 1; i < 32; i++)
    if(strcmp(s, regs[i]) == 0)
      return cpu.gpr[i];

  //no reg name matched
  *success = false;
  return 0;
}
