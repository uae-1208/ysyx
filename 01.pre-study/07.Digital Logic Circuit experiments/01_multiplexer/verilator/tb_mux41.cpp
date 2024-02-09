#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
//contains the top class of our Verilated mux41 module
#include "Vmux41.h"


#define MAX_SIM_TIME 200
vluint64_t sim_time = 0;
Vmux41 *dut = new Vmux41;
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


	dut->X0 = 0b11;
	dut->X1 = 0b10;
	dut->X2 = 0b01;
	dut->X3 = 0b00;

	dut->Y = 0b00;  step_and_dump_wave();
	dut->Y = 0b01;  step_and_dump_wave();
	dut->Y = 0b10;  step_and_dump_wave();
	dut->Y = 0b11;  step_and_dump_wave();step_and_dump_wave();
	

	m_trace->close();
	delete dut;
	exit(EXIT_SUCCESS);
}
