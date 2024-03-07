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
        tracep->declBit(c+51,"clk", false,-1);
        tracep->declBit(c+52,"rst", false,-1);
        tracep->declBus(c+53,"inst", false,-1, 31,0);
        tracep->declBus(c+54,"pc", false,-1, 31,0);
        tracep->declBit(c+51,"rv32 clk", false,-1);
        tracep->declBit(c+52,"rv32 rst", false,-1);
        tracep->declBus(c+53,"rv32 inst", false,-1, 31,0);
        tracep->declBus(c+54,"rv32 pc", false,-1, 31,0);
        tracep->declBus(c+55,"rv32 rs1", false,-1, 4,0);
        tracep->declBus(c+56,"rv32 rs2", false,-1, 4,0);
        tracep->declBus(c+57,"rv32 rd", false,-1, 4,0);
        tracep->declBus(c+58,"rv32 funct7", false,-1, 6,0);
        tracep->declBus(c+59,"rv32 type4", false,-1, 2,0);
        tracep->declBit(c+65,"rv32 m1", false,-1);
        tracep->declBus(c+66,"rv32 aluc", false,-1, 0,0);
        tracep->declBus(c+60,"rv32 result", false,-1, 31,0);
        tracep->declBus(c+61,"rv32 src1", false,-1, 31,0);
        tracep->declBus(c+62,"rv32 src2", false,-1, 31,0);
        tracep->declBus(c+35,"rv32 imm", false,-1, 31,0);
        tracep->declBus(c+61,"rv32 num1", false,-1, 31,0);
        tracep->declBus(c+36,"rv32 num2", false,-1, 31,0);
        tracep->declBit(c+51,"rv32 PC_inst clk", false,-1);
        tracep->declBit(c+52,"rv32 PC_inst rst", false,-1);
        tracep->declBus(c+54,"rv32 PC_inst pc", false,-1, 31,0);
        tracep->declBus(c+1,"rv32 PC_inst clk_div4", false,-1, 1,0);
        tracep->declBus(c+53,"rv32 control_unit_inst inst", false,-1, 31,0);
        tracep->declBus(c+57,"rv32 control_unit_inst rd_11_7", false,-1, 4,0);
        tracep->declBus(c+55,"rv32 control_unit_inst rs1_19_15", false,-1, 4,0);
        tracep->declBus(c+56,"rv32 control_unit_inst rs2_24_20", false,-1, 4,0);
        tracep->declBus(c+58,"rv32 control_unit_inst fun7_31_25", false,-1, 6,0);
        tracep->declBus(c+59,"rv32 control_unit_inst type1", false,-1, 2,0);
        tracep->declBit(c+66,"rv32 control_unit_inst aluc", false,-1);
        tracep->declBit(c+65,"rv32 control_unit_inst m1", false,-1);
        tracep->declBus(c+63,"rv32 control_unit_inst opcode_6_0", false,-1, 6,0);
        tracep->declBus(c+64,"rv32 control_unit_inst fun3_14_12", false,-1, 2,0);
        tracep->declBit(c+51,"rv32 register_file_inst clk", false,-1);
        tracep->declBit(c+52,"rv32 register_file_inst rst", false,-1);
        tracep->declBit(c+65,"rv32 register_file_inst wen", false,-1);
        tracep->declBus(c+55,"rv32 register_file_inst rs1", false,-1, 4,0);
        tracep->declBus(c+56,"rv32 register_file_inst rs2", false,-1, 4,0);
        tracep->declBus(c+57,"rv32 register_file_inst rd", false,-1, 4,0);
        tracep->declBus(c+60,"rv32 register_file_inst result", false,-1, 31,0);
        tracep->declBus(c+61,"rv32 register_file_inst src1", false,-1, 31,0);
        tracep->declBus(c+62,"rv32 register_file_inst src2", false,-1, 31,0);
        tracep->declBus(c+2,"rv32 register_file_inst i", false,-1, 31,0);
        {int i; for (i=0; i<32; i++) {
                tracep->declBus(c+3+i*1,"rv32 register_file_inst regs", true,(i+0), 31,0);}}
        tracep->declBus(c+56,"rv32 imm_extend_inst rs2", false,-1, 4,0);
        tracep->declBus(c+58,"rv32 imm_extend_inst funct7", false,-1, 6,0);
        tracep->declBus(c+59,"rv32 imm_extend_inst type3", false,-1, 2,0);
        tracep->declBus(c+35,"rv32 imm_extend_inst imm32", false,-1, 31,0);
        tracep->declBus(c+37,"rv32 imm_extend_inst imm_12", false,-1, 11,0);
        tracep->declBus(c+56,"rv32 imm_extend_inst RISB_type_inst rs2", false,-1, 4,0);
        tracep->declBus(c+58,"rv32 imm_extend_inst RISB_type_inst funct7", false,-1, 6,0);
        tracep->declBus(c+59,"rv32 imm_extend_inst RISB_type_inst type2", false,-1, 2,0);
        tracep->declBus(c+37,"rv32 imm_extend_inst RISB_type_inst imm_12", false,-1, 11,0);
        tracep->declBus(c+37,"rv32 imm_extend_inst Extend_12_inst imm_12", false,-1, 11,0);
        tracep->declBus(c+35,"rv32 imm_extend_inst Extend_12_inst imm_12_to_32", false,-1, 31,0);
        tracep->declBus(c+67,"rv32 i1 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+68,"rv32 i1 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+69,"rv32 i1 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+36,"rv32 i1 out", false,-1, 31,0);
        tracep->declBus(c+65,"rv32 i1 key", false,-1, 0,0);
        tracep->declArray(c+38,"rv32 i1 lut", false,-1, 65,0);
        tracep->declBus(c+67,"rv32 i1 i0 NR_KEY", false,-1, 31,0);
        tracep->declBus(c+68,"rv32 i1 i0 KEY_LEN", false,-1, 31,0);
        tracep->declBus(c+69,"rv32 i1 i0 DATA_LEN", false,-1, 31,0);
        tracep->declBus(c+70,"rv32 i1 i0 HAS_DEFAULT", false,-1, 31,0);
        tracep->declBus(c+36,"rv32 i1 i0 out", false,-1, 31,0);
        tracep->declBus(c+65,"rv32 i1 i0 key", false,-1, 0,0);
        tracep->declBus(c+71,"rv32 i1 i0 default_out", false,-1, 31,0);
        tracep->declArray(c+38,"rv32 i1 i0 lut", false,-1, 65,0);
        tracep->declBus(c+72,"rv32 i1 i0 PAIR_LEN", false,-1, 31,0);
        {int i; for (i=0; i<2; i++) {
                tracep->declQuad(c+41+i*2,"rv32 i1 i0 pair_list", true,(i+0), 32,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+45+i*1,"rv32 i1 i0 key_list", true,(i+0), 0,0);}}
        {int i; for (i=0; i<2; i++) {
                tracep->declBus(c+47+i*1,"rv32 i1 i0 data_list", true,(i+0), 31,0);}}
        tracep->declBus(c+49,"rv32 i1 i0 lut_out", false,-1, 31,0);
        tracep->declBit(c+50,"rv32 i1 i0 hit", false,-1);
        tracep->declBus(c+73,"rv32 i1 i0 i", false,-1, 31,0);
        tracep->declBit(c+66,"rv32 alu_inst aluc", false,-1);
        tracep->declBus(c+61,"rv32 alu_inst num1", false,-1, 31,0);
        tracep->declBus(c+36,"rv32 alu_inst num2", false,-1, 31,0);
        tracep->declBus(c+60,"rv32 alu_inst result", false,-1, 31,0);
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
        tracep->fullCData(oldp+1,(vlTOPp->rv32__DOT__PC_inst__DOT__clk_div4),2);
        tracep->fullIData(oldp+2,(vlTOPp->rv32__DOT__register_file_inst__DOT__i),32);
        tracep->fullIData(oldp+3,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0]),32);
        tracep->fullIData(oldp+4,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[1]),32);
        tracep->fullIData(oldp+5,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[2]),32);
        tracep->fullIData(oldp+6,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[3]),32);
        tracep->fullIData(oldp+7,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[4]),32);
        tracep->fullIData(oldp+8,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[5]),32);
        tracep->fullIData(oldp+9,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[6]),32);
        tracep->fullIData(oldp+10,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[7]),32);
        tracep->fullIData(oldp+11,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[8]),32);
        tracep->fullIData(oldp+12,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[9]),32);
        tracep->fullIData(oldp+13,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[10]),32);
        tracep->fullIData(oldp+14,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[11]),32);
        tracep->fullIData(oldp+15,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[12]),32);
        tracep->fullIData(oldp+16,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[13]),32);
        tracep->fullIData(oldp+17,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[14]),32);
        tracep->fullIData(oldp+18,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[15]),32);
        tracep->fullIData(oldp+19,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[16]),32);
        tracep->fullIData(oldp+20,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[17]),32);
        tracep->fullIData(oldp+21,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[18]),32);
        tracep->fullIData(oldp+22,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[19]),32);
        tracep->fullIData(oldp+23,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[20]),32);
        tracep->fullIData(oldp+24,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[21]),32);
        tracep->fullIData(oldp+25,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[22]),32);
        tracep->fullIData(oldp+26,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[23]),32);
        tracep->fullIData(oldp+27,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[24]),32);
        tracep->fullIData(oldp+28,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[25]),32);
        tracep->fullIData(oldp+29,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[26]),32);
        tracep->fullIData(oldp+30,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[27]),32);
        tracep->fullIData(oldp+31,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[28]),32);
        tracep->fullIData(oldp+32,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[29]),32);
        tracep->fullIData(oldp+33,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[30]),32);
        tracep->fullIData(oldp+34,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[31]),32);
        tracep->fullIData(oldp+35,(((0xfffff000U & 
                                     ((- (IData)((1U 
                                                  & ((IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12) 
                                                     >> 0xbU)))) 
                                      << 0xcU)) | (IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12))),32);
        tracep->fullIData(oldp+36,(vlTOPp->rv32__DOT__num2),32);
        tracep->fullSData(oldp+37,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12),12);
        tracep->fullWData(oldp+38,(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3),66);
        tracep->fullQData(oldp+41,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[0]),33);
        tracep->fullQData(oldp+43,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[1]),33);
        tracep->fullBit(oldp+45,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[0]));
        tracep->fullBit(oldp+46,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[1]));
        tracep->fullIData(oldp+47,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[0]),32);
        tracep->fullIData(oldp+48,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[1]),32);
        tracep->fullIData(oldp+49,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out),32);
        tracep->fullBit(oldp+50,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit));
        tracep->fullBit(oldp+51,(vlTOPp->clk));
        tracep->fullBit(oldp+52,(vlTOPp->rst));
        tracep->fullIData(oldp+53,(vlTOPp->inst),32);
        tracep->fullIData(oldp+54,(vlTOPp->pc),32);
        tracep->fullCData(oldp+55,((0x1fU & (vlTOPp->inst 
                                             >> 0xfU))),5);
        tracep->fullCData(oldp+56,((0x1fU & (vlTOPp->inst 
                                             >> 0x14U))),5);
        tracep->fullCData(oldp+57,((0x1fU & (vlTOPp->inst 
                                             >> 7U))),5);
        tracep->fullCData(oldp+58,((0x7fU & (vlTOPp->inst 
                                             >> 0x19U))),7);
        tracep->fullCData(oldp+59,(((0x13U == (0x7fU 
                                               & vlTOPp->inst))
                                     ? 2U : 0U)),3);
        tracep->fullIData(oldp+60,((((0U == (0x1fU 
                                             & (vlTOPp->inst 
                                                >> 0xfU)))
                                      ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                     [(0x1fU & (vlTOPp->inst 
                                                >> 0xfU))]) 
                                    + vlTOPp->rv32__DOT__num2)),32);
        tracep->fullIData(oldp+61,(((0U == (0x1fU & 
                                            (vlTOPp->inst 
                                             >> 0xfU)))
                                     ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                    [(0x1fU & (vlTOPp->inst 
                                               >> 0xfU))])),32);
        tracep->fullIData(oldp+62,(((0U == (0x1fU & 
                                            (vlTOPp->inst 
                                             >> 0x14U)))
                                     ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                    [(0x1fU & (vlTOPp->inst 
                                               >> 0x14U))])),32);
        tracep->fullCData(oldp+63,((0x7fU & vlTOPp->inst)),7);
        tracep->fullCData(oldp+64,((7U & (vlTOPp->inst 
                                          >> 0xcU))),3);
        tracep->fullBit(oldp+65,(1U));
        tracep->fullBit(oldp+66,(0U));
        tracep->fullIData(oldp+67,(2U),32);
        tracep->fullIData(oldp+68,(1U),32);
        tracep->fullIData(oldp+69,(0x20U),32);
        tracep->fullIData(oldp+70,(0U),32);
        tracep->fullIData(oldp+71,(0U),32);
        tracep->fullIData(oldp+72,(0x21U),32);
        tracep->fullIData(oldp+73,(2U),32);
    }
}
