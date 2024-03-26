#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vrv32.h"
#include "verilated_vcd_c.h"
#include "Vrv32__Dpi.h"
#include "svdpi.h"
#include "../include/common.h"
#include "../include/utils.h"



VerilatedVcdC* tfp = new VerilatedVcdC(); //导出vcd波形需要加此语句
Vrv32 *top = new Vrv32("top");
vluint64_t main_time = 0;  //initial 仿真时间



/********extern functions or variables********/
extern char *diff_so_file;
extern int  difftest_port;
extern long img_size;
extern NPCState npc_state;
extern void   init_monitor(int, char *[]);
extern void   sdb_mainloop() ;
extern int    is_exit_status_bad();
extern void   ebreak(int station, int inst);
extern void   init_difftest(char *ref_so_file, long img_size, int port);
extern word_t pmem_read(paddr_t addr, int len); 
/*********************************************/

#define start_time 4

void ebreak(int station, int inst)
{
  if(Verilated::gotFinish())
    return;
    
  if(main_time >= start_time)   // at the begining (main_time < start_time and before the reset), all regs are zeros
  {
    npc_state.halt_ret = top->rv32__DOT__register_file_inst__DOT__regs[10]; //a0
    npc_state.halt_pc = top->pc;

    switch(station)
    {
      case HIT_TRAP:
        npc_state.state = NPC_END;
        break;

      case ABORT:
      default:
        npc_state.state = NPC_ABORT;
        break;
    }

    Verilated::gotFinish(true);
  }
}


static inline word_t inst_fetch(word_t pc, int len)
{
  return pmem_read(pc, len);
}

void single_cycle(void) 
{
  if(!Verilated::gotFinish())
  { 
    top->clk = 0; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
    top->clk = 1; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
    
    if(main_time >= start_time)   // at the begining (main_time < start_time and before the reset), all regs are zeros
      top->inst = inst_fetch(top->pc, 4);
  }
}

static void reset(void)
{
  top->rst = 0; single_cycle();
  top->rst = 1; single_cycle();
  top->rst = 0; 
  // single_cycle();
  // single_cycle(); 
}

static void init_verilator(void)
{
  Verilated::traceEverOn(true); //导出vcd波形需要加此语句

  top->trace(tfp, 0);
  tfp->open("waveform.vcd"); //打开vcd

  reset();  //复位
}

int main(int argc, char *argv[])
{
  /* Initialize the monitor. */
  init_monitor(argc, argv);

  /* Initialize the verilator. */
  init_verilator();

  /* Initialize differential testing. */
  init_difftest(diff_so_file, img_size, difftest_port);

  /* Receive commands from user. */
  sdb_mainloop();

  /* End the simulation */
  top->final();
  tfp->close();
  delete top;

  return is_exit_status_bad();
}