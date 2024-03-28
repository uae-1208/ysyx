// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vrv32__Syms.h"


//======================

void Vrv32::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vrv32::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vrv32::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vrv32::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vrv32::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+151,"clk", false,-1);
        tracep->declBit(c+152,"rst", false,-1);
        tracep->declBit(c+151,"rv32 clk", false,-1);
        tracep->declBit(c+152,"rv32 rst", false,-1);
        tracep->declBit(c+1,"rv32 clk0_flag", false,-1);
        tracep->declBit(c+2,"rv32 clk1_flag", false,-1);
        tracep->declBit(c+3,"rv32 clk2_flag", false,-1);
        tracep->declBus(c+41,"rv32 rs1", false,-1, 4,0);
        tracep->declBus(c+42,"rv32 rs2", false,-1, 4,0);
        tracep->declBus(c+43,"rv32 rd", false,-1, 4,0);
        tracep->declBus(c+44,"rv32 funct3", false,-1, 2,0);
        tracep->declBus(c+45,"rv32 funct7", false,-1, 6,0);
        tracep->declBus(c+46,"rv32 inst", false,-1, 31,0);
        tracep->declBus(c+4,"rv32 pc", false,-1, 31,0);
        tracep->declBus(c+47,"rv32 type4", false,-1, 2,0);
        tracep->declBit(c+48,"rv32 wen_r", false,-1);
        tracep->declBit(c+49,"rv32 wen_m", false,-1);
        tracep->declBus(c+50,"rv32 wmask", false,-1, 7,0);
        tracep->declBit(c+51,"rv32 m1", false,-1);
        tracep->declBit(c+52,"rv32 m2", false,-1);
        tracep->declBit(c+53,"rv32 m3", false,-1);
        tracep->declBus(c+54,"rv32 m4", false,-1, 1,0);
        tracep->declBit(c+55,"rv32 m5", false,-1);
        tracep->declBus(c+56,"rv32 aluc", false,-1, 1,0);
        tracep->declBus(c+5,"rv32 PCadd4", false,-1, 31,0);
        tracep->declBus(c+57,"rv32 result", false,-1, 31,0);
        tracep->declBus(c+58,"rv32 rin", false,-1, 31,0);
        tracep->declBus(c+59,"rv32 src1", false,-1, 31,0);
        tracep->declBus(c+60,"rv32 src2", false,-1, 31,0);
        tracep->declBus(c+61,"rv32 imm", false,-1, 31,0);
        tracep->declBus(c+62,"rv32 num1", false,-1, 31,0);
        tracep->declBus(c+63,"rv32 num2", false,-1, 31,0);
        tracep->declBus(c+64,"rv32 raddr", false,-1, 31,0);
        tracep->declBus(c+65,"rv32 mem_rdata", false,-1, 31,0);
        tracep->declBit(c+151,"rv32 clk_count_inst clk", false,-1);
        tracep->declBit(c+152,"rv32 clk_count_inst rst", false,-1);
        tracep->declBit(c+1,"rv32 clk_count_inst clk0_flag", false,-1);
        tracep->declBit(c+2,"rv32 clk_count_inst clk1_flag", false,-1);
        tracep->declBit(c+3,"rv32 clk_count_inst clk2_flag", false,-1);
        tracep->declBus(c+6,"rv32 clk_count_inst clk_cnt", false,-1, 1,0);
        tracep->declBit(c+151,"rv32 PC_inst clk", false,-1);
        tracep->declBit(c+152,"rv32 PC_inst rst", false,-1);
        tracep->declBit(c+53,"rv32 PC_inst m3", false,-1);
        tracep->declBit(c+3,"rv32 PC_inst clk2_flag", false,-1);
        tracep->declBus(c+57,"rv32 PC_inst result", false,-1, 31,0);
        tracep->declBus(c+5,"rv32 PC_inst PCadd4", false,-1, 31,0);
        tracep->declBus(c+4,"rv32 PC_inst pc", false,-1, 31,0);
        tracep->declBus(c+66,"rv32 PC_inst pc_temp", false,-1, 31,0);
        tracep->declBus(c+154,"rv32 PC_inst i3 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 PC_inst i3 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 PC_inst i3 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+66,"rv32 PC_inst i3 out", false,-1, 31,0);
        tracep->declBus(c+53,"rv32 PC_inst i3 key", false,-1, 0,0);
        tracep->declArray(c+67,"rv32 PC_inst i3 lut", false,-1, 65,0);
        tracep->declBus(c+154,"rv32 PC_inst i3 i0 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 PC_inst i3 i0 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 PC_inst i3 i0 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+157,"rv32 PC_inst i3 i0 HAS_DEFAULT", false,-1, 31,0);
        tracep->declBus(c+66,"rv32 PC_inst i3 i0 out", false,-1, 31,0);
        tracep->declBus(c+53,"rv32 PC_inst i3 i0 key", false,-1, 0,0);
        tracep->declBus(c+158,"rv32 PC_inst i3 i0 default_out", false,-1, 31,0);
        tracep->declArray(c+67,"rv32 PC_inst i3 i0 lut", false,-1, 65,0);
        tracep->declBus(c+159,"rv32 PC_inst i3 i0 PAIR_LEN", false,-1, 31,0);
        {int i; for (i=0; i<2; i++) {
                tracep->declQuad(c+70+i*2,"rv32 PC_inst i3 i0 pair_list", true,(i+0), 32,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+74+i*1,"rv32 PC_inst i3 i0 key_list", true,(i+0), 0,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+76+i*1,"rv32 PC_inst i3 i0 data_list", true,(i+0), 31,0);}}
        tracep->declBus(c+78,"rv32 PC_inst i3 i0 lut_out", false,-1, 31,0);
        tracep->declBit(c+79,"rv32 PC_inst i3 i0 hit", false,-1);
        tracep->declBus(c+160,"rv32 PC_inst i3 i0 i", false,-1, 31,0);
        tracep->declBit(c+151,"rv32 pc_reg_inst clk", false,-1);
        tracep->declBit(c+152,"rv32 pc_reg_inst rst", false,-1);
        tracep->declBit(c+1,"rv32 pc_reg_inst clk0_flag", false,-1);
        tracep->declBit(c+3,"rv32 pc_reg_inst clk2_flag", false,-1);
        tracep->declBus(c+65,"rv32 pc_reg_inst mem_rdata", false,-1, 31,0);
        tracep->declBus(c+46,"rv32 pc_reg_inst inst", false,-1, 31,0);
        tracep->declBus(c+7,"rv32 pc_reg_inst inst_reg", false,-1, 31,0);
        tracep->declBit(c+161,"rv32 mem_inst valid", false,-1);
        tracep->declBit(c+80,"rv32 mem_inst wen_m", false,-1);
        tracep->declBus(c+50,"rv32 mem_inst wmask", false,-1, 7,0);
        tracep->declBus(c+57,"rv32 mem_inst waddr", false,-1, 31,0);
        tracep->declBus(c+60,"rv32 mem_inst wdata", false,-1, 31,0);
        tracep->declBus(c+64,"rv32 mem_inst raddr", false,-1, 31,0);
        tracep->declBus(c+65,"rv32 mem_inst rdata", false,-1, 31,0);
        tracep->declBit(c+80,"rv32 mem_inst wen", false,-1);
        tracep->declBus(c+46,"rv32 control_unit_inst inst", false,-1, 31,0);
        tracep->declBus(c+43,"rv32 control_unit_inst rd_11_7", false,-1, 4,0);
        tracep->declBus(c+41,"rv32 control_unit_inst rs1_19_15", false,-1, 4,0);
        tracep->declBus(c+42,"rv32 control_unit_inst rs2_24_20", false,-1, 4,0);
        tracep->declBus(c+44,"rv32 control_unit_inst fun3_14_12", false,-1, 2,0);
        tracep->declBus(c+45,"rv32 control_unit_inst fun7_31_25", false,-1, 6,0);
        tracep->declBus(c+47,"rv32 control_unit_inst type1", false,-1, 2,0);
        tracep->declBus(c+56,"rv32 control_unit_inst aluc", false,-1, 1,0);
        tracep->declBit(c+48,"rv32 control_unit_inst wen_r", false,-1);
        tracep->declBit(c+49,"rv32 control_unit_inst wen_m", false,-1);
        tracep->declBus(c+50,"rv32 control_unit_inst wmask", false,-1, 7,0);
        tracep->declBit(c+51,"rv32 control_unit_inst m1", false,-1);
        tracep->declBit(c+52,"rv32 control_unit_inst m2", false,-1);
        tracep->declBit(c+53,"rv32 control_unit_inst m3", false,-1);
        tracep->declBus(c+54,"rv32 control_unit_inst m4", false,-1, 1,0);
        tracep->declBit(c+55,"rv32 control_unit_inst m5", false,-1);
        tracep->declBus(c+81,"rv32 control_unit_inst opcode_6_0", false,-1, 6,0);
        tracep->declBit(c+151,"rv32 register_file_inst clk", false,-1);
        tracep->declBit(c+152,"rv32 register_file_inst rst", false,-1);
        tracep->declBit(c+153,"rv32 register_file_inst wen_r", false,-1);
        tracep->declBus(c+41,"rv32 register_file_inst rs1", false,-1, 4,0);
        tracep->declBus(c+42,"rv32 register_file_inst rs2", false,-1, 4,0);
        tracep->declBus(c+43,"rv32 register_file_inst rd", false,-1, 4,0);
        tracep->declBus(c+58,"rv32 register_file_inst rin", false,-1, 31,0);
        tracep->declBus(c+59,"rv32 register_file_inst src1", false,-1, 31,0);
        tracep->declBus(c+60,"rv32 register_file_inst src2", false,-1, 31,0);
        tracep->declBus(c+8,"rv32 register_file_inst i", false,-1, 31,0);
        {int i; for (i=0; i<32; i++) {
                tracep->declBus(c+9+i*1,"rv32 register_file_inst regs", true,(i+0), 31,0);}}
        tracep->declBit(c+153,"rv32 register_file_inst wen", false,-1);
        tracep->declBus(c+41,"rv32 imm_extend_inst rs1", false,-1, 4,0);
        tracep->declBus(c+42,"rv32 imm_extend_inst rs2", false,-1, 4,0);
        tracep->declBus(c+43,"rv32 imm_extend_inst rd", false,-1, 4,0);
        tracep->declBus(c+44,"rv32 imm_extend_inst funct3", false,-1, 2,0);
        tracep->declBus(c+45,"rv32 imm_extend_inst funct7", false,-1, 6,0);
        tracep->declBus(c+47,"rv32 imm_extend_inst type3", false,-1, 2,0);
        tracep->declBus(c+61,"rv32 imm_extend_inst imm32", false,-1, 31,0);
        tracep->declBus(c+82,"rv32 imm_extend_inst imm_12", false,-1, 11,0);
        tracep->declBus(c+83,"rv32 imm_extend_inst imm_20", false,-1, 19,0);
        tracep->declBus(c+84,"rv32 imm_extend_inst imm_12_to_32", false,-1, 31,0);
        tracep->declBus(c+85,"rv32 imm_extend_inst imm_20_to_32", false,-1, 31,0);
        tracep->declBus(c+42,"rv32 imm_extend_inst RISB_type_inst rs2", false,-1, 4,0);
        tracep->declBus(c+43,"rv32 imm_extend_inst RISB_type_inst rd", false,-1, 4,0);
        tracep->declBus(c+45,"rv32 imm_extend_inst RISB_type_inst funct7", false,-1, 6,0);
        tracep->declBus(c+47,"rv32 imm_extend_inst RISB_type_inst type2", false,-1, 2,0);
        tracep->declBus(c+82,"rv32 imm_extend_inst RISB_type_inst imm_12", false,-1, 11,0);
        tracep->declBus(c+41,"rv32 imm_extend_inst UJ_type_inst rs1", false,-1, 4,0);
        tracep->declBus(c+42,"rv32 imm_extend_inst UJ_type_inst rs2", false,-1, 4,0);
        tracep->declBus(c+44,"rv32 imm_extend_inst UJ_type_inst funct3", false,-1, 2,0);
        tracep->declBus(c+45,"rv32 imm_extend_inst UJ_type_inst funct7", false,-1, 6,0);
        tracep->declBus(c+47,"rv32 imm_extend_inst UJ_type_inst type2", false,-1, 2,0);
        tracep->declBus(c+83,"rv32 imm_extend_inst UJ_type_inst imm_20", false,-1, 19,0);
        tracep->declBus(c+82,"rv32 imm_extend_inst Extend_12_inst imm_12", false,-1, 11,0);
        tracep->declBus(c+84,"rv32 imm_extend_inst Extend_12_inst imm_12_to_32", false,-1, 31,0);
        tracep->declBus(c+83,"rv32 imm_extend_inst Extend_20_inst imm_20", false,-1, 19,0);
        tracep->declBus(c+85,"rv32 imm_extend_inst Extend_20_inst imm_20_to_32", false,-1, 31,0);
        tracep->declBus(c+154,"rv32 i1 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 i1 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i1 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+62,"rv32 i1 out", false,-1, 31,0);
        tracep->declBus(c+51,"rv32 i1 key", false,-1, 0,0);
        tracep->declArray(c+86,"rv32 i1 lut", false,-1, 65,0);
        tracep->declBus(c+154,"rv32 i1 i0 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 i1 i0 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i1 i0 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+157,"rv32 i1 i0 HAS_DEFAULT", false,-1, 31,0);
        tracep->declBus(c+62,"rv32 i1 i0 out", false,-1, 31,0);
        tracep->declBus(c+51,"rv32 i1 i0 key", false,-1, 0,0);
        tracep->declBus(c+158,"rv32 i1 i0 default_out", false,-1, 31,0);
        tracep->declArray(c+86,"rv32 i1 i0 lut", false,-1, 65,0);
        tracep->declBus(c+159,"rv32 i1 i0 PAIR_LEN", false,-1, 31,0);
        {int i; for (i=0; i<2; i++) {
                tracep->declQuad(c+89+i*2,"rv32 i1 i0 pair_list", true,(i+0), 32,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+93+i*1,"rv32 i1 i0 key_list", true,(i+0), 0,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+95+i*1,"rv32 i1 i0 data_list", true,(i+0), 31,0);}}
        tracep->declBus(c+97,"rv32 i1 i0 lut_out", false,-1, 31,0);
        tracep->declBit(c+98,"rv32 i1 i0 hit", false,-1);
        tracep->declBus(c+160,"rv32 i1 i0 i", false,-1, 31,0);
        tracep->declBus(c+154,"rv32 i2 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 i2 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i2 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+63,"rv32 i2 out", false,-1, 31,0);
        tracep->declBus(c+52,"rv32 i2 key", false,-1, 0,0);
        tracep->declArray(c+99,"rv32 i2 lut", false,-1, 65,0);
        tracep->declBus(c+154,"rv32 i2 i0 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 i2 i0 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i2 i0 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+157,"rv32 i2 i0 HAS_DEFAULT", false,-1, 31,0);
        tracep->declBus(c+63,"rv32 i2 i0 out", false,-1, 31,0);
        tracep->declBus(c+52,"rv32 i2 i0 key", false,-1, 0,0);
        tracep->declBus(c+158,"rv32 i2 i0 default_out", false,-1, 31,0);
        tracep->declArray(c+99,"rv32 i2 i0 lut", false,-1, 65,0);
        tracep->declBus(c+159,"rv32 i2 i0 PAIR_LEN", false,-1, 31,0);
        {int i; for (i=0; i<2; i++) {
                tracep->declQuad(c+102+i*2,"rv32 i2 i0 pair_list", true,(i+0), 32,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+106+i*1,"rv32 i2 i0 key_list", true,(i+0), 0,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+108+i*1,"rv32 i2 i0 data_list", true,(i+0), 31,0);}}
        tracep->declBus(c+110,"rv32 i2 i0 lut_out", false,-1, 31,0);
        tracep->declBit(c+111,"rv32 i2 i0 hit", false,-1);
        tracep->declBus(c+160,"rv32 i2 i0 i", false,-1, 31,0);
        tracep->declBus(c+162,"rv32 i4 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+154,"rv32 i4 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i4 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+58,"rv32 i4 out", false,-1, 31,0);
        tracep->declBus(c+54,"rv32 i4 key", false,-1, 1,0);
        tracep->declArray(c+112,"rv32 i4 lut", false,-1, 135,0);
        tracep->declBus(c+162,"rv32 i4 i0 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+154,"rv32 i4 i0 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i4 i0 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+157,"rv32 i4 i0 HAS_DEFAULT", false,-1, 31,0);
        tracep->declBus(c+58,"rv32 i4 i0 out", false,-1, 31,0);
        tracep->declBus(c+54,"rv32 i4 i0 key", false,-1, 1,0);
        tracep->declBus(c+158,"rv32 i4 i0 default_out", false,-1, 31,0);
        tracep->declArray(c+112,"rv32 i4 i0 lut", false,-1, 135,0);
        tracep->declBus(c+163,"rv32 i4 i0 PAIR_LEN", false,-1, 31,0);
        {int i; for (i=0; i<4; i++) {
                tracep->declQuad(c+117+i*2,"rv32 i4 i0 pair_list", true,(i+0), 33,0);}}
        {int i; for (i=0; i<4; i++) {
                tracep->declBus(c+125+i*1,"rv32 i4 i0 key_list", true,(i+0), 1,0);}}
        {int i; for (i=0; i<4; i++) {
                tracep->declBus(c+129+i*1,"rv32 i4 i0 data_list", true,(i+0), 31,0);}}
        tracep->declBus(c+133,"rv32 i4 i0 lut_out", false,-1, 31,0);
        tracep->declBit(c+134,"rv32 i4 i0 hit", false,-1);
        tracep->declBus(c+164,"rv32 i4 i0 i", false,-1, 31,0);
        tracep->declBus(c+154,"rv32 i5 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 i5 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i5 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+64,"rv32 i5 out", false,-1, 31,0);
        tracep->declBus(c+135,"rv32 i5 key", false,-1, 0,0);
        tracep->declArray(c+136,"rv32 i5 lut", false,-1, 65,0);
        tracep->declBus(c+154,"rv32 i5 i0 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+155,"rv32 i5 i0 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+156,"rv32 i5 i0 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+157,"rv32 i5 i0 HAS_DEFAULT", false,-1, 31,0);
        tracep->declBus(c+64,"rv32 i5 i0 out", false,-1, 31,0);
        tracep->declBus(c+135,"rv32 i5 i0 key", false,-1, 0,0);
        tracep->declBus(c+158,"rv32 i5 i0 default_out", false,-1, 31,0);
        tracep->declArray(c+136,"rv32 i5 i0 lut", false,-1, 65,0);
        tracep->declBus(c+159,"rv32 i5 i0 PAIR_LEN", false,-1, 31,0);
        {int i; for (i=0; i<2; i++) {
                tracep->declQuad(c+139+i*2,"rv32 i5 i0 pair_list", true,(i+0), 32,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+143+i*1,"rv32 i5 i0 key_list", true,(i+0), 0,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+145+i*1,"rv32 i5 i0 data_list", true,(i+0), 31,0);}}
        tracep->declBus(c+147,"rv32 i5 i0 lut_out", false,-1, 31,0);
        tracep->declBit(c+148,"rv32 i5 i0 hit", false,-1);
        tracep->declBus(c+160,"rv32 i5 i0 i", false,-1, 31,0);
        tracep->declBus(c+56,"rv32 alu_inst aluc", false,-1, 1,0);
        tracep->declBus(c+62,"rv32 alu_inst num1", false,-1, 31,0);
        tracep->declBus(c+63,"rv32 alu_inst num2", false,-1, 31,0);
        tracep->declBus(c+57,"rv32 alu_inst result", false,-1, 31,0);
        tracep->declBus(c+165,"rv32 alu_inst temp", false,-1, 31,0);
        tracep->declBus(c+149,"rv32 alu_inst num1_cplm", false,-1, 31,0);
        tracep->declBus(c+150,"rv32 alu_inst num2_cplm", false,-1, 31,0);
    }
}

void Vrv32::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vrv32::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vrv32::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,((0U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
        tracep->fullBit(oldp+2,((1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
        tracep->fullBit(oldp+3,((2U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
        tracep->fullIData(oldp+4,(vlTOPp->rv32__DOT__pc),32);
        tracep->fullIData(oldp+5,(((IData)(4U) + vlTOPp->rv32__DOT__pc)),32);
        tracep->fullCData(oldp+6,(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt),2);
        tracep->fullIData(oldp+7,(vlTOPp->rv32__DOT__pc_reg_inst__DOT__inst_reg),32);
        tracep->fullIData(oldp+8,(vlTOPp->rv32__DOT__register_file_inst__DOT__i),32);
        tracep->fullIData(oldp+9,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0]),32);
        tracep->fullIData(oldp+10,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[1]),32);
        tracep->fullIData(oldp+11,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[2]),32);
        tracep->fullIData(oldp+12,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[3]),32);
        tracep->fullIData(oldp+13,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[4]),32);
        tracep->fullIData(oldp+14,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[5]),32);
        tracep->fullIData(oldp+15,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[6]),32);
        tracep->fullIData(oldp+16,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[7]),32);
        tracep->fullIData(oldp+17,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[8]),32);
        tracep->fullIData(oldp+18,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[9]),32);
        tracep->fullIData(oldp+19,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[10]),32);
        tracep->fullIData(oldp+20,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[11]),32);
        tracep->fullIData(oldp+21,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[12]),32);
        tracep->fullIData(oldp+22,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[13]),32);
        tracep->fullIData(oldp+23,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[14]),32);
        tracep->fullIData(oldp+24,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[15]),32);
        tracep->fullIData(oldp+25,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[16]),32);
        tracep->fullIData(oldp+26,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[17]),32);
        tracep->fullIData(oldp+27,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[18]),32);
        tracep->fullIData(oldp+28,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[19]),32);
        tracep->fullIData(oldp+29,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[20]),32);
        tracep->fullIData(oldp+30,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[21]),32);
        tracep->fullIData(oldp+31,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[22]),32);
        tracep->fullIData(oldp+32,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[23]),32);
        tracep->fullIData(oldp+33,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[24]),32);
        tracep->fullIData(oldp+34,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[25]),32);
        tracep->fullIData(oldp+35,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[26]),32);
        tracep->fullIData(oldp+36,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[27]),32);
        tracep->fullIData(oldp+37,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[28]),32);
        tracep->fullIData(oldp+38,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[29]),32);
        tracep->fullIData(oldp+39,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[30]),32);
        tracep->fullIData(oldp+40,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[31]),32);
        tracep->fullCData(oldp+41,((0x1fU & (vlTOPp->rv32__DOT__inst 
                                             >> 0xfU))),5);
        tracep->fullCData(oldp+42,((0x1fU & (vlTOPp->rv32__DOT__inst 
                                             >> 0x14U))),5);
        tracep->fullCData(oldp+43,((0x1fU & (vlTOPp->rv32__DOT__inst 
                                             >> 7U))),5);
        tracep->fullCData(oldp+44,((7U & (vlTOPp->rv32__DOT__inst 
                                          >> 0xcU))),3);
        tracep->fullCData(oldp+45,((0x7fU & (vlTOPp->rv32__DOT__inst 
                                             >> 0x19U))),7);
        tracep->fullIData(oldp+46,(vlTOPp->rv32__DOT__inst),32);
        tracep->fullCData(oldp+47,(vlTOPp->rv32__DOT__type4),3);
        tracep->fullBit(oldp+48,(vlTOPp->rv32__DOT__wen_r));
        tracep->fullBit(oldp+49,(vlTOPp->rv32__DOT__wen_m));
        tracep->fullCData(oldp+50,(vlTOPp->rv32__DOT__wmask),8);
        tracep->fullBit(oldp+51,(vlTOPp->rv32__DOT__m1));
        tracep->fullBit(oldp+52,(vlTOPp->rv32__DOT__m2));
        tracep->fullBit(oldp+53,(vlTOPp->rv32__DOT__m3));
        tracep->fullCData(oldp+54,(vlTOPp->rv32__DOT__m4),2);
        tracep->fullBit(oldp+55,(vlTOPp->rv32__DOT__m5));
        tracep->fullCData(oldp+56,(vlTOPp->rv32__DOT__aluc),2);
        tracep->fullIData(oldp+57,(vlTOPp->rv32__DOT__result),32);
        tracep->fullIData(oldp+58,(vlTOPp->rv32__DOT__rin),32);
        tracep->fullIData(oldp+59,(vlTOPp->rv32__DOT__src1),32);
        tracep->fullIData(oldp+60,(vlTOPp->rv32__DOT__src2),32);
        tracep->fullIData(oldp+61,(vlTOPp->rv32__DOT__imm),32);
        tracep->fullIData(oldp+62,(vlTOPp->rv32__DOT__num1),32);
        tracep->fullIData(oldp+63,(vlTOPp->rv32__DOT__num2),32);
        tracep->fullIData(oldp+64,(vlTOPp->rv32__DOT__raddr),32);
        tracep->fullIData(oldp+65,(vlTOPp->rv32__DOT__mem_rdata),32);
        tracep->fullIData(oldp+66,(vlTOPp->rv32__DOT__PC_inst__DOT__pc_temp),32);
        tracep->fullWData(oldp+67,(vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3),66);
        tracep->fullQData(oldp+70,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[0]),33);
        tracep->fullQData(oldp+72,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[1]),33);
        tracep->fullBit(oldp+74,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[0]));
        tracep->fullBit(oldp+75,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[1]));
        tracep->fullIData(oldp+76,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[0]),32);
        tracep->fullIData(oldp+77,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[1]),32);
        tracep->fullIData(oldp+78,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out),32);
        tracep->fullBit(oldp+79,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__hit));
        tracep->fullBit(oldp+80,(vlTOPp->rv32__DOT____Vcellinp__mem_inst__wen_m));
        tracep->fullCData(oldp+81,((0x7fU & vlTOPp->rv32__DOT__inst)),7);
        tracep->fullSData(oldp+82,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12),12);
        tracep->fullIData(oldp+83,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20),20);
        tracep->fullIData(oldp+84,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32),32);
        tracep->fullIData(oldp+85,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32),32);
        tracep->fullWData(oldp+86,(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3),66);
        tracep->fullQData(oldp+89,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[0]),33);
        tracep->fullQData(oldp+91,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[1]),33);
        tracep->fullBit(oldp+93,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[0]));
        tracep->fullBit(oldp+94,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[1]));
        tracep->fullIData(oldp+95,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[0]),32);
        tracep->fullIData(oldp+96,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[1]),32);
        tracep->fullIData(oldp+97,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out),32);
        tracep->fullBit(oldp+98,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit));
        tracep->fullWData(oldp+99,(vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3),66);
        tracep->fullQData(oldp+102,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[0]),33);
        tracep->fullQData(oldp+104,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[1]),33);
        tracep->fullBit(oldp+106,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[0]));
        tracep->fullBit(oldp+107,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[1]));
        tracep->fullIData(oldp+108,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[0]),32);
        tracep->fullIData(oldp+109,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[1]),32);
        tracep->fullIData(oldp+110,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__lut_out),32);
        tracep->fullBit(oldp+111,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__hit));
        tracep->fullWData(oldp+112,(vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3),136);
        tracep->fullQData(oldp+117,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[0]),34);
        tracep->fullQData(oldp+119,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[1]),34);
        tracep->fullQData(oldp+121,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[2]),34);
        tracep->fullQData(oldp+123,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[3]),34);
        tracep->fullCData(oldp+125,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[0]),2);
        tracep->fullCData(oldp+126,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[1]),2);
        tracep->fullCData(oldp+127,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[2]),2);
        tracep->fullCData(oldp+128,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[3]),2);
        tracep->fullIData(oldp+129,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[0]),32);
        tracep->fullIData(oldp+130,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[1]),32);
        tracep->fullIData(oldp+131,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[2]),32);
        tracep->fullIData(oldp+132,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[3]),32);
        tracep->fullIData(oldp+133,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out),32);
        tracep->fullBit(oldp+134,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit));
        tracep->fullBit(oldp+135,(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber2));
        tracep->fullWData(oldp+136,(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3),66);
        tracep->fullQData(oldp+139,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list[0]),33);
        tracep->fullQData(oldp+141,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list[1]),33);
        tracep->fullBit(oldp+143,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list[0]));
        tracep->fullBit(oldp+144,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list[1]));
        tracep->fullIData(oldp+145,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list[0]),32);
        tracep->fullIData(oldp+146,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list[1]),32);
        tracep->fullIData(oldp+147,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__lut_out),32);
        tracep->fullBit(oldp+148,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__hit));
        tracep->fullIData(oldp+149,(((IData)(1U) + 
                                     (~ vlTOPp->rv32__DOT__num1))),32);
        tracep->fullIData(oldp+150,(((IData)(1U) + 
                                     (~ vlTOPp->rv32__DOT__num2))),32);
        tracep->fullBit(oldp+151,(vlTOPp->clk));
        tracep->fullBit(oldp+152,(vlTOPp->rst));
        tracep->fullBit(oldp+153,(((IData)(vlTOPp->rv32__DOT__wen_r) 
                                   & (1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt)))));
        tracep->fullIData(oldp+154,(2U),32);
        tracep->fullIData(oldp+155,(1U),32);
        tracep->fullIData(oldp+156,(0x20U),32);
        tracep->fullIData(oldp+157,(0U),32);
        tracep->fullIData(oldp+158,(0U),32);
        tracep->fullIData(oldp+159,(0x21U),32);
        tracep->fullIData(oldp+160,(2U),32);
        tracep->fullBit(oldp+161,(1U));
        tracep->fullIData(oldp+162,(4U),32);
        tracep->fullIData(oldp+163,(0x22U),32);
        tracep->fullIData(oldp+164,(4U),32);
        tracep->fullIData(oldp+165,(0xfffffffeU),32);
    }
}
