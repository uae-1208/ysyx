#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vrv32.h"
#include "verilated_vcd_c.h"
 

vluint64_t main_time = 0;  //initial 仿真时间
static const uint32_t inst[] = {
  0xffc10113,  // addi	sp,sp,-4
  0xffc10113,  // addi	sp,sp,-4
  0x06460593,  // addi a1,a2,100
};

 
static uint32_t pmem_read(uint32_t pc)
{
  assert(pc >= 0x80000000);
  return inst[pc - 0x80000000];
}

static void single_cycle(Vrv32 *top, VerilatedVcdC* tfp) 
{
  top->clk = 0; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
  top->clk = 1; top->eval(); tfp->dump(main_time);  main_time++; //推动仿真时间
}

int main(void)
{
  Verilated::traceEverOn(true); //导出vcd波形需要加此语句

  VerilatedVcdC* tfp = new VerilatedVcdC(); //导出vcd波形需要加此语句

  Vrv32 *top = new Vrv32("top");
  top->trace(tfp, 0);
  tfp->open("waveform.vcd"); //打开vcd

  //复位
  top->rst = 1;   single_cycle(top, tfp);   
  top->rst = 0;   single_cycle(top, tfp);  

  top->inst = pmem_read(top->pc);
  single_cycle(top, tfp);    
  single_cycle(top, tfp);    
  single_cycle(top, tfp);    

  top->inst = pmem_read(top->pc);
  single_cycle(top, tfp);    
  single_cycle(top, tfp);    
  single_cycle(top, tfp);    

  top->inst = pmem_read(top->pc);
  single_cycle(top, tfp);    
  single_cycle(top, tfp);    
  single_cycle(top, tfp);    

  // while(!main_time < 2 && !Verilated::gotFinish())
  // {                                                                                                                                                                                                            
  //   top->inst = pmem_read(top->pc);
  //   single_cycle(top);

  //   tfp->dump(main_time); //dump wave
  //   main_time++; //推动仿真时间
  // }

  top->final();
  tfp->close();
  delete top;
  return 0;
}