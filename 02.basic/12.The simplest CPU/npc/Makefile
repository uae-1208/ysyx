MODULE=rv32
CSRCS = $(shell find $(abspath ./csrc) -name "*.cpp")
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
VSRCS += $(shell find $(abspath ./vsrc/*) -name "*.v")

.PHONY:sim
sim: waveform.vcd


.PHONY:verilate
verilate: .stamp.verilate


.PHONY:build
build: obj_dir/V$(MODULE)


.PHONY:waves
waves: waveform.vcd
	@echo
	@echo "### WAVES ###"
	gtkwave waveform.vcd


waveform.vcd: ./obj_dir/V$(MODULE)
	@echo
	@echo "### SIMULATING ###"
	@./obj_dir/V$(MODULE) #+verilator+rand+reset+2


#This builds our simulation executable from the testbench and the converted sources.
#We tell Make to change the working directory to obj_dir, 
#use the build file named Valu.mk and build the target named Valu
#----------------------------------------------------------------------------------
./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE)


#This converts our .v source to C++ and generates build files 
#for building the simulation executable. 
#We use -Wall to enable all C++ errors, 
#--trace to enable waveform tracing, 
#-cc .v to convert our .v module to C++, 
#and --exe tb_alu.cpp to tell Verilator which file is our C++ testbench.
# -Wno-STMTDLY 避免弹出所有warning
# -Wno-MODDUP 避免“Duplicate declaration”报错
# --top-module $(MODULE) 确定底层模块，否则会将$(VSRCS)中的第一个文件前缀当成顶层模块
#----------------------------------------------------------------------------------
.stamp.verilate: $(VSRCS) $(CSRCS)
	@echo
	@echo "### VERILATING ###"
	verilator -Wno-STMTDLY -Wno-MODDUP --trace --top-module $(MODULE) -cc $(VSRCS) --exe $(CSRCS)
	@touch .stamp.verilate


#Note that there is an aditional make lint target, 
#which calls Verilator with --lint-only. 
#This is useful to quickly parse your Verilog/SystemVerilog source files 
#and check for problems. 
#This can be used to check over your sources even if you’re not using Verilator for simulating.
#----------------------------------------------------------------------------------
.PHONY:lint
lint: $(MODULE).v
	#-lint-only- 告诉 Verilator 进行 lint 但不生成任何仿真输出]
	verilator --lint-only $(MODULE).v


.PHONY: clean
clean:
	rm -rf .stamp.*;
	rm -rf ./obj_dir
	rm -rf waveform.vcd
	
