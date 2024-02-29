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

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() 
{
  //"\33[1;31m" means red，"\n\33[0m" means returning to default
  printf("\33[1;31mRegName  Hex_Value       Dec_Value\n\33[0m");
  printf("\33[1;33m$%s\t\33[0m 0x%08x\t %010u\n", "pc", cpu.pc, cpu.pc);
  for(int i = 0; i < 32; i++)
  {
    printf("\33[1;33m$%s\t \33[0m", regs[i]);
    printf("0x%08x\t %010u\n", cpu.gpr[i], cpu.gpr[i]);
  }
}

void isa_single_reg_display(char *reg_name) 
{
  int i;
  //pc
  printf("\33[1;31mRegName  Hex_Value       U-Dec_Value       Dec_Value\n\33[0m");
  if(strcmp(reg_name, "pc") == 0)
  {
    printf("\33[1;33m$%s\t\33[0m 0x%08x\t %010u %010d\n", "pc", cpu.pc, cpu.pc, cpu.pc);
    return;
  }

  //reg $0
  if(strcmp(reg_name, regs[0]) == 0)
  {
    printf("\33[1;33m$%s\t\33[0m 0x%08x\t %010u\t   %-10d\n", "$0", cpu.gpr[1], cpu.gpr[1], cpu.gpr[1]);
    return;
  }      

  //others
  for(i = 1; i < 32; i++)
    if(strcmp(reg_name, regs[i]) == 0)
    {
      printf("\33[1;33m$%s\t\33[0m 0x%08x\t %010u\t   %-10d\n", regs[i], cpu.gpr[i], cpu.gpr[i], cpu.gpr[i]);
      return;
    }

  Log_R("No register %s.", reg_name);
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
