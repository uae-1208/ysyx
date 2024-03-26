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
#include <memory/paddr.h>


// #define CONFIG_IRINGBUF 1
// #define CONFIG_MTRACE   1
// #define CONFIG_FTRACE   1


word_t vaddr_ifetch(vaddr_t addr, int len) {
#ifdef CONFIG_MTRACE
  word_t data = paddr_read(addr, len);
  printf("\33[1;33m[mtrace]\33[0m rd_inst  \33[1;33maddr:\33[0m 0x%08x  \33[1;33mdata:\33[0m 0x%08x\n", addr, data);
  log_write("[mtrace] rd_inst  addr: 0x%08x  data: 0x%08x\n", addr, data); 
  return data;
#else
  return paddr_read(addr, len);
#endif
}

word_t vaddr_read(vaddr_t addr, int len) {
#ifdef CONFIG_MTRACE
  word_t data = paddr_read(addr, len);
  printf("\33[1;33m[mtrace]\33[0m rd_mem   \33[1;33maddr:\33[0m 0x%08x  \33[1;33mdata:\33[0m 0x%08x\n", addr, data);
  log_write("[mtrace] rd_mem  addr: 0x%08x  data: 0x%08x\n", addr, data); 
  return data;
#else
  return paddr_read(addr, len);
#endif
}

void vaddr_write(vaddr_t addr, int len, word_t data) {
#ifdef CONFIG_MTRACE
  printf("\33[1;33m[mtrace]\33[0m wr_mem   \33[1;33maddr:\33[0m 0x%08x  \33[1;33mdata:\33[0m 0x%08x\n", addr, data);
  log_write("[mtrace] wr_mem   addr: 0x%08x  data: 0x%08x\n", addr, data); 
#endif
  paddr_write(addr, len, data);
}
