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
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>
#include <memory/host.h>

/*
typedef struct {
  word_t gpr[MUXDEF(CONFIG_RVE, 16, 32)];
  vaddr_t pc;
} MUXDEF(CONFIG_RV64, riscv64_CPU_state, riscv32_CPU_state);
*/


__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) 
{
  if(direction == DIFFTEST_TO_REF)
    memcpy(guest_to_host(RESET_VECTOR), buf, n);
  else
    assert(0);
}

__EXPORT void difftest_regcpy(void *dut, bool direction) {
  if(direction == DIFFTEST_TO_REF)
  {
    memcpy(&cpu, dut, sizeof(cpu));
    // cpu.pc = dut->pc;
    // for(int i = 0; i < 32; i++)
    //   cpu.gpr[i] = dut->gpr[i];
  }
  else if(direction == DIFFTEST_TO_DUT)
  {
    memcpy(dut, &cpu, sizeof(cpu));
    // dut->pc = cpu.pc;
    // for(int i = 0; i < 32; i++)
    //   dut->gpr[i] = cpu.gpr[i];
  }
  else
    assert(0);
}

__EXPORT void difftest_exec(uint64_t n) {
  cpu_exec(n);
}

__EXPORT void difftest_raise_intr(word_t NO) {
  assert(0);
}

__EXPORT void difftest_init(int port) {
  void init_mem();
  init_mem();
  /* Perform ISA dependent initialization. */
  init_isa();
}
