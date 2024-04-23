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

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  cpu.csr[MEPC] = epc;

#ifdef CONFIG_ETRACE
  printf("\33[1;33m[etrace]\33[0m \33[1;33mmstatus:\33[0m 0x%08x, "
         "\33[1;33mmepc:\33[0m 0x%08x, \33[1;33mmcause:\33[0m 0x%08x\n", 
          cpu.csr[MSTATUS], cpu.csr[MEPC], cpu.csr[MCAUSE]);
  log_write ("[etrace] mstatus: 0x%08x, mepc: 0x%08x, mcause: 0x%08x\n", 
              cpu.csr[MSTATUS], cpu.csr[MEPC], cpu.csr[MCAUSE]);
#endif

  return cpu.csr[MTVEC];
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
