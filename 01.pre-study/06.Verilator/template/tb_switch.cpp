#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
//contains the top class of our Verilated SWITCH module
#include "Vswitch.h"


#define MAX_SIM_TIME 200
vluint64_t sim_time = 0;


int main(int argc, char** argv, char** env) 
{
	Verilated::commandArgs(argc, argv);
	Vswitch *dut = new Vswitch;
   
	/*The next four lines set up the waveform dumping.*/
	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	//The parameter 5 simply limits the depth of the trace to 5 levels down the device under test.
	dut->trace(m_trace, 5);
	m_trace->open("waveform.vcd");

	while (sim_time < MAX_SIM_TIME) 
	{
		//dut->clk ^= 1;
		
		int a = rand() & 1;
		int b = rand() & 1;
		dut->a = a;
		dut->b = b;
	
		dut->eval();
		//writes all the traced signal values into our waveform dump file
		m_trace->dump(sim_time);
		sim_time++;
	}

	m_trace->close();
	delete dut;
	exit(EXIT_SUCCESS);
}
