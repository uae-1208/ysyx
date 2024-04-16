#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vrv32.h"
#include "verilated_vcd_c.h"
#include "Vrv32__Dpi.h"
#include "svdpi.h"


#define HIT_GOOD_TRAP 1
#define HIT_BAD_TRAP  2
#define ABORT         3


VerilatedVcdC* tfp = new VerilatedVcdC(); //导出vcd波形需要加此语句
Vrv32 *top = new Vrv32("top");
vluint64_t main_time = 0;  //initial 仿真时间
static const uint32_t inst[] = {
// 80000000 <_start>:
  0x00000413,          //	li	s0,0
  0x00009117,          //	auipc	sp,0x9
  0xffc10113,          //	add	sp,sp,-4 # 80009000 <_end>
  0x00c000ef,          //	jal	80000018 <_trm_init>
// 80000010 <main>:
  0x00000513,          //	li	a0,0
  0x00008067,          //	ret
// 80000018 <_trm_init>:
  0xff010113,          //	add	sp,sp,-16
  0x00000517,          //	auipc	a0,0x0
  0x01450513,          //	add	a0,a0,20 # 80000030 <_etext>
  0x00112623,          //	sw	ra,12(sp)
  0xfe9ff0ef,          //	jal	80000010 <main>
  0x00050513,          // mv	a0,a0
  0x00100073,          // ebreak
  0x0000006f,          // j	80000034 <_trm_init+0x1c>

//   0xffc10113,    //addi	sp,sp,-4
//   0x06400593,    //li	  a1,100
//   0x06458613,    //add	a2,a1,100
//   0x0c860693,    //add	a3,a2,200
//   0xed468713,    //add	a4,a3,-300
//   0xe7070793,    //add	a5,a4,-400
//   0x00009117,    //auipc	sp,0x9
//   0x80178813,    //add	a6,a5,-2047
//   0x7fa80893,    //add	a7,a6,2042
//   0x00000517,    //auipc	a0,0x0
//   0x7fa88893,    //add	a7,a7,2042
//   0x00100073,    //ebreak
//   0x06458613,    //add	a2,a1,100
//   0x0c860693,    //add	a3,a2,200
};

 
static uint32_t pmem_read(uint32_t pc)
{
  if(pc < 0x80000000)
    return 0;
  if((pc - 0x80000000) % 4 != 0)
    return 0;

  return inst[(pc - 0x80000000) / 4];
}



extern void ebreak(int station, int inst)
{
  switch(station)
  {
    case HIT_GOOD_TRAP:
      printf("\33[1;32m HIT GOOD TRAP \33[0m at pc = 0x%08x   ", top->pc);
      printf("\33[1;35m Instruction \33[0m = 0x%08x\n", inst);
      break;
    
    case HIT_BAD_TRAP:
      printf("\33[1;31m HIT BAD TRAP\33[0m at pc = 0x%08x   ", top->pc);
      printf("\33[1;32m Instruction \33[0m = 0x%08x\n", inst);
      break;

    case ABORT:
    default:
      if(main_time >= 4)
      {
        printf("\33[1;31m ABORT\33[0m at pc = 0x%08x   ", top->pc);
        printf("\33[1;32m Instruction \33[0m = 0x%08x\n", inst);
      }
      break;
  }

  if(main_time >= 4)
    Verilated::gotFinish(true);
}


static void single_cycle(void) 
{
  if(!Verilated::gotFinish())
  { 
    top->clk = 0; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
    top->clk = 1; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
    top->inst = pmem_read(top->pc);
  }
}


static void reset(void)
{
  top->rst = 0; single_cycle();
  top->rst = 1; single_cycle();
  top->rst = 0; single_cycle();
  single_cycle(); 
}


int main(void)
{
  Verilated::traceEverOn(true); //导出vcd波形需要加此语句

  top->trace(tfp, 0);
  tfp->open("waveform.vcd"); //打开vcd

  //复位
  reset();

  while(!Verilated::gotFinish())
  {                                           
    if(main_time > 100)
      break;                                                                                                                                                                 
    single_cycle(); single_cycle(); single_cycle();
  }

  single_cycle();    

  top->final();
  tfp->close();
  delete top;
  return 0;
}