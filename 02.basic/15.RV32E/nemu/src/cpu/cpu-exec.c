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

#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
// #define CONFIG_IRINGBUF 1
// #define CONFIG_MTRACE   1
// #define CONFIG_FTRACE   1

/*****************************iringbuf*****************************/
#ifdef CONFIG_IRINGBUF 

#define MAX_iringbuf_size  20
struct IRINGBUF
{
  // char *inst_buf[MAX_iringbuf_size];
  char inst_buf[MAX_iringbuf_size][64];
  int head, tail;
};

static struct IRINGBUF iringbuf = {
  // .inst_buf = {NULL},
  .inst_buf = {""},
  .head = 0,
  .tail = 0
};

static void append_iringbuf(char *s)
{
  // if(iringbuf.inst_buf[iringbuf.head] != NULL)
  if(strcmp(iringbuf.inst_buf[iringbuf.head], ""))    //the iringbuf is not currently empty
  {
    iringbuf.tail = (iringbuf.tail + 1) % MAX_iringbuf_size;  
    if(iringbuf.head == iringbuf.tail)                //the iringbuf is currently full
      iringbuf.head = (iringbuf.head + 1) % MAX_iringbuf_size;
  }

  // iringbuf.inst_buf[iringbuf.tail] = (char*)malloc(strlen(s));
  // assert(iringbuf.inst_buf[iringbuf.tail] != NULL);
  strcpy(iringbuf.inst_buf[iringbuf.tail], s);
}

static void display_iringbuf(void)
{
  int i = iringbuf.head;
  if(iringbuf.inst_buf[i] == NULL)
  return;

  Log("Display inst iringbuf:");
  while(i != iringbuf.tail)
  {
    printf("\33[1;33m[iringbuf]\33[0m       %s\n", iringbuf.inst_buf[i]);
    log_write("[iringbuf]       %s\n", iringbuf.inst_buf[i]); 
    i = (i + 1) % MAX_iringbuf_size;
  }
  printf("\33[1;33m[iringbuf]\33[0m \33[1;31m---->\33[0m %s\n", iringbuf.inst_buf[iringbuf.tail]);
  log_write("[iringbuf] ----> %s\n", iringbuf.inst_buf[iringbuf.tail]); 
}

// static void clear_iringbuf(void)
// {
//   for(int i = 0; i < MAX_iringbuf_size; i++)
//     if(iringbuf.inst_buf[i] != NULL)
//       free(iringbuf.inst_buf[i]);
// }

#endif
/******************************************************************/


/******************************ftrace******************************/
#ifdef CONFIG_FTRACE 

extern void RET_Log(uint32_t pc, uint32_t npc);
extern void J_Log(uint32_t pc, uint32_t npc);
#define OPCODE(inst)  ((inst) & 0x7f)

#endif
/******************************************************************/


#define MAX_INST_TO_PRINT 10

CPU_state cpu = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0; // unit: us
static bool g_print_step = false;

void device_update();
extern bool scan_all_wps(void);

static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
  if (ITRACE_COND) { log_write("%s\n", _this->logbuf); }
#endif
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }
  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));

  if(scan_all_wps())
    nemu_state.state = NEMU_STOP;
}

static void exec_once(Decode *s, vaddr_t pc) {
  s->pc = pc;
  s->snpc = pc;
  isa_exec_once(s);
  if(s->isa.inst.val == 0x00100073) // After excuting 'ebreak', npc should remain, but +=4.
  {
    s->dnpc -= 4;
    s->snpc -= 4;
  }
  cpu.pc = s->dnpc;
#ifdef CONFIG_ITRACE
  char *p = s->logbuf;
  p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);
  int ilen = s->snpc - s->pc;
  int i;
  uint8_t *inst = (uint8_t *)&s->isa.inst.val;
  for (i = ilen - 1; i >= 0; i --) {
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;

#ifndef CONFIG_ISA_loongarch32r
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst.val, ilen);
#else
  p[0] = '\0'; // the upstream llvm does not support loongarch32r
#endif
#endif

#ifdef CONFIG_IRINGBUF 
  append_iringbuf(s->logbuf);
#endif

#ifdef CONFIG_FTRACE
  if(s->isa.inst.val == 0x00008067)  //ret
    RET_Log(s->pc, s->dnpc);
  else if((OPCODE(s->isa.inst.val)==0b1100111) || (OPCODE(s->isa.inst.val)== 0b1101111))  //jalr or jal
    J_Log(s->pc, s->dnpc);
#endif

}

static void execute(uint64_t n) {
  Decode s;
  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);
    g_nr_guest_inst ++;
    trace_and_difftest(&s, cpu.pc);
    if (nemu_state.state != NEMU_RUNNING) break;
    IFDEF(CONFIG_DEVICE, device_update());
  }
}

static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}

void assert_fail_msg() {
  isa_reg_display();
  statistic();
}

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  uint64_t timer_start = get_time();

  execute(n);

  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;

    case NEMU_END: case NEMU_ABORT:
#ifdef CONFIG_IRINGBUF 
      display_iringbuf();
      // clear_iringbuf();
#endif
      Log("nemu: %s at pc = " FMT_WORD,
          (nemu_state.state == NEMU_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
           (nemu_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          nemu_state.halt_pc);
      // fall through
    case NEMU_QUIT: statistic();
  }
}
