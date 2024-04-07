#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vrv32.h"
#include "verilated_vcd_c.h"
#include "Vrv32__Dpi.h"
#include "svdpi.h"
#include "../include/common.h"
#include "../include/utils.h"
#include "../include/debug.h"



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
extern void   init_difftest(char *ref_so_file, long img_size, int port);
extern word_t pmem_r(paddr_t addr, int len); 
extern void   pmem_w(paddr_t addr, int len, word_t data);
extern void   ebreak(int station, int inst);                   // control_unit.v
extern int    pmem_read(int raddr);                            // mem.v
extern int    pmem_read_inst(int pc);
extern void   pmem_write(int waddr, int wdata, char wmask);    // mem.v
/*********************************************/

#define start_time 3

static const char *alu_names[16] = {
  "Unit_ALU", "Unit_MEM", "Unit_CU1", "Unit_CU2",
  "Unit_CU3", "Unit_CU4", "Unit_CU5", "Unit_CU6",
  "Unit_CU7", "Unit_CU8", "Unit_CU9", "Unit_CU10",
  "Unit_CU11","Unit_IE1", "Unit_IE2", "Unit_IE3"
};

extern void ebreak(int station, int inst, char unit)
{
  if(Verilated::gotFinish())
    return;
    // Log("maintime = %ld, state = %d, pc = 0x%08x, inst = 0x%08x", main_time, npc_state.state, top->rv32__DOT__pc, top->rv32__DOT__inst);

  //虽然波形图上inst随pc同时变化，但通过打印二者会发现inst会在pc变化之后才改变（这是因为二者都发生变化了之后才输出至波形图的）
  //然而，这个延时会导致decode错误，然后调用了 “ebreak(`ABORT, inst);”
  if(main_time >= start_time + 1)   // at the begining (main_time < start_time and before the reset), all regs are zeros
  {
    npc_state.halt_ret = top->rv32__DOT__register_file_inst__DOT__regs[10]; //a0
    npc_state.halt_pc = top->rv32__DOT__pc;

    assert( (unit == Unit_ALU) || (unit == Unit_CU1) || (unit == Unit_CU2) || (unit == Unit_CU3) || 
            (unit == Unit_CU4) || (unit == Unit_CU5) || (unit == Unit_CU6) || (unit == Unit_CU7) || 
            (unit == Unit_CU8) || (unit == Unit_CU9) || (unit == Unit_CU10)|| (unit == Unit_CU11)||
            (unit == Unit_MEM) || (unit == Unit_IE1) || (unit == Unit_IE2) || (unit == Unit_IE3));

    Log("Ebreak takes place in the %s", alu_names[unit]);
    Log("maintime = %ld, state = %d, pc = 0x%08x, inst = 0x%08x", main_time, npc_state.state, top->rv32__DOT__pc, top->rv32__DOT__inst);

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


extern int pmem_read(int raddr)
{
  static int data = 0xdeadbeaf;
  if(top->clk == 0)
    return data;

  if(main_time >= start_time)
  {
    data = pmem_r(raddr, 4);
    return data; 
    // return pmem_r((raddr & ~0x3u), 4);
  } 
  else
    return 0xdeadbeaf;
}


void pmem_write(int waddr, int wdata, char wmask)
{
  if(top->clk == 0)
    return;

  switch (wmask)
  {
    case WByte: pmem_w(waddr, 1, wdata);
                break;
    case WHalf: pmem_w(waddr, 2, wdata);
                break;
    case WWord: pmem_w(waddr, 4, wdata);
                break;
    default:    assert(0);
                break;
  }
}


void single_cycle(void) 
{
  if(!Verilated::gotFinish())
  { 
    top->clk = 0; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
    top->clk = 1; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
  }
}

static void reset(void)
{
  top->rst = 0; single_cycle();
  top->rst = 1; single_cycle();
  top->rst = 0; 
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




// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include "Vrv32.h"
// #include "verilated_vcd_c.h"
// #include "Vrv32__Dpi.h"
// #include "svdpi.h"


// #define HIT_GOOD_TRAP 1
// #define ABORT         2
// // #define HIT_BAD_TRAP  2
// // #define ABORT         3


// VerilatedVcdC* tfp = new VerilatedVcdC(); //导出vcd波形需要加此语句
// Vrv32 *top = new Vrv32("top");
// vluint64_t main_time = 0;  //initial 仿真时间
// static  uint32_t inst[] = {
// // 80000000 <_start>:
//   0x00000413,          //	li	s0,0
//   0x00009117,          //	auipc	sp,0x9
//   0xffc10113,          //	add	sp,sp,-4 # 80009000 <_end>
//   0x00c000ef,          //	jal	80000018 <_trm_init>
// // 80000010 <main>:
//   0x00000513,          //	li	a0,0
//   0x00008067,          //	ret
// // 80000018 <_trm_init>:
//   0xff010113,          //	add	sp,sp,-16
//   0x00000517,          //	auipc	a0,0x0
//   0x01450513,          //	add	a0,a0,20 # 80000030 <_etext>
//   0x00112623,          //	sw	ra,12(sp)
//   0xfe9ff0ef,          //	jal	80000010 <main>
//   0x00050513,          // mv	a0,a0
//   0x00100073,          // ebreak
//   0x0000006f,          // j	80000034 <_trm_init+0x1c>

// //   0xffc10113,    //addi	sp,sp,-4
// //   0x06400593,    //li	  a1,100
// //   0x06458613,    //add	a2,a1,100
// //   0x0c860693,    //add	a3,a2,200
// //   0xed468713,    //add	a4,a3,-300
// //   0xe7070793,    //add	a5,a4,-400
// //   0x00009117,    //auipc	sp,0x9
// //   0x80178813,    //add	a6,a5,-2047
// //   0x7fa80893,    //add	a7,a6,2042
// //   0x00000517,    //auipc	a0,0x0
// //   0x7fa88893,    //add	a7,a7,2042
// //   0x00100073,    //ebreak
// //   0x06458613,    //add	a2,a1,100
// //   0x0c860693,    //add	a3,a2,200
// };

 
// extern int pmem_read(int raddr)
// {
//   if(raddr < 0x80000000)
//     return 0;
//   if((raddr - 0x80000000) % 4 != 0)
//     return 0;

//   return inst[(raddr - 0x80000000) / 4];
// }


// void pmem_write(int waddr, int wdata, char wmask)
// {
//   printf("inst=0x%08x, waddr=0x%08x, wdata=0x%08x, wmask=0x%08x\n\n" ,top->rv32__DOT__pc, waddr, wdata, wmask);
//   inst[(waddr - 0x80000000) / 4] = wdata;
  
  
//   // switch (wmask)
//   // {
//   //   // case WByte: pmem_w(waddr, 1, wdata);
//   //   //             break;
//   //   // case WHalf: pmem_w(waddr, 2, wdata);
//   //   //             break;
//   //   case WWord: pmem_w(waddr, 4, wdata);
//   //               break;
//   //   default:    assert(0);
//   //               break;
//   // }
// }

// extern void ebreak(int station, int inst)
// {
//   switch(station)
//   {
//     case HIT_GOOD_TRAP:
//       printf("\33[1;32m HIT GOOD TRAP \33[0m at pc = 0x%08x   ", top->rv32__DOT__pc);
//       printf("\33[1;35m Instruction \33[0m = 0x%08x\n", inst);
//       break;
    
//     // case HIT_BAD_TRAP:
//     //   printf("\33[1;31m HIT BAD TRAP\33[0m at pc = 0x%08x   ", top->rv32__DOT__pc);
//     //   printf("\33[1;32m Instruction \33[0m = 0x%08x\n", inst);
//     //   break;

//     case ABORT:
//     default:
//       if(main_time >= 4)
//       {
//         printf("\33[1;31m ABORT\33[0m at pc = 0x%08x   ", top->rv32__DOT__pc);
//         printf("\33[1;32m Instruction \33[0m = 0x%08x\n", inst);
//       }
//       break;
//   }

//   if(main_time >= 4)
//     Verilated::gotFinish(true);
// }


// void single_cycle(void) 
// {
//   if(!Verilated::gotFinish())
//   { 
//     top->clk = 0; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
//     top->clk = 1; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
//     // top->inst = pmem_read(top->pc);
//   }
// }


// static void reset(void)
// {
//   top->rst = 0; single_cycle();
//   top->rst = 1; single_cycle();
//   top->rst = 0; single_cycle();
//   single_cycle(); 
// }


// int main(void)
// {
//   Verilated::traceEverOn(true); //导出vcd波形需要加此语句

//   top->trace(tfp, 0);
//   tfp->open("waveform.vcd"); //打开vcd

//   //复位
//   reset();

//   while(!Verilated::gotFinish())
//   {                                           
//     if(main_time > 100)
//       break;                                                                                                                                                                 
//     single_cycle(); single_cycle(); single_cycle();
//   }

//   single_cycle();    

//   top->final();
//   tfp->close();
//   delete top;
//   return 0;
// }