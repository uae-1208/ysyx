#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
//contains the top class of our Verilated mux41 module
#include "Vtop.h"


#define MAX_SIM_TIME 200
vluint64_t sim_time = 0;
Vtop *dut = new Vtop;
VerilatedVcdC *m_trace = new VerilatedVcdC;


void step_and_dump_wave()
{
	dut->eval();
	sim_time++;
	//writes all the traced signal values into our waveform dump file
	m_trace->dump(sim_time);
}


int main(int argc, char** argv, char** env) 
{
	Verilated::commandArgs(argc, argv);
	/*The next four lines set up the waveform dumping.*/
	Verilated::traceEverOn(true);
	//The parameter 5 simply limits the depth of the trace to 5 levels down the device under test.
	dut->trace(m_trace, 5);
	m_trace->open("waveform.vcd");


	step_and_dump_wave();
	//取反
	dut->option = 2;
	dut->A = 3;
	dut->b = 12;
	step_and_dump_wave();
	//与
	dut->option = 3;
	step_and_dump_wave();
	//或
	dut->option = 4;
	step_and_dump_wave();
	//异或
	dut->option = 5;
	step_and_dump_wave();
	//比较
	dut->option = 6;
	step_and_dump_wave();
	dut->A = 12;
	dut->b = 3;
	step_and_dump_wave();
	dut->A = 12;
	dut->b = 12;
	step_and_dump_wave();
	//相等
	dut->option = 7;
	step_and_dump_wave();
	dut->A = 12;
	dut->b = 3;
	step_and_dump_wave();
	dut->A = 3;
	dut->b = 12;
	step_and_dump_wave();

	// //加法  溢出             不溢出    
	// //正 正 3,7          	 3,4      
	// //正 负 				 3，12(-4)
	// //负 正 				 12(-4),7        
	// //负 负 12(-4),9(-7)     12(-4)，13(-3)  
	// dut->option = 0;
	// //正 正 溢出√
	// dut->A = 3;
	// dut->b = 7;
	// step_and_dump_wave();
	// //正 正 不溢出√
	// dut->A = 3;
	// dut->b = 4;
	// step_and_dump_wave();
	// //正 负 不溢出√
	// dut->A = 3;
	// dut->b = 12;
	// step_and_dump_wave();
	// //负 正 不溢出√
	// dut->A = 12;
	// dut->b = 7;
	// step_and_dump_wave();
	// //负 负 溢出√
	// dut->A = 12;
	// dut->b = 9;
	// step_and_dump_wave();
	// //负 负 不溢出
	// dut->A = 12;
	// dut->b = 13;
	// step_and_dump_wave();

	// //减法  溢出             不溢出    
	// //正 正                  3，7
	// //正 负 7,12(-4)         3，12(-4)
	// //负 正 12(-4),7         12(-4)，3 
	// //负 负 				 12(-4)，9(-7)     
	// dut->option = 1;
	// //正 正 不溢出√
	// dut->A = 3;
	// dut->b = 7;
	// step_and_dump_wave();
	// //正 负 溢出√
	// dut->A = 7;
	// dut->b = 12;
	// step_and_dump_wave();
	// //正 负 不溢出√
	// dut->A = 3;
	// dut->b = 12;
	// step_and_dump_wave();
	// //负 正 溢出√
	// dut->A = 12;
	// dut->b = 7;
	// step_and_dump_wave();
	// //负 正 不溢出√
	// dut->A = 12;
	// dut->b = 3;
	// step_and_dump_wave();
	// //负 负 不溢出
	// dut->A = 12;
	// dut->b = 9;
	// step_and_dump_wave();	

	step_and_dump_wave();	
	
	m_trace->close();
	delete dut;
	exit(EXIT_SUCCESS);
}
