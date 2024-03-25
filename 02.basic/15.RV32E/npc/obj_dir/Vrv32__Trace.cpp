// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vrv32__Syms.h"


void Vrv32::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vrv32::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[1U])) {
            tracep->chgBit(oldp+0,((1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
            tracep->chgBit(oldp+1,((2U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
            tracep->chgCData(oldp+2,(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt),2);
            tracep->chgIData(oldp+3,(vlTOPp->rv32__DOT__register_file_inst__DOT__i),32);
            tracep->chgIData(oldp+4,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0]),32);
            tracep->chgIData(oldp+5,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[1]),32);
            tracep->chgIData(oldp+6,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[2]),32);
            tracep->chgIData(oldp+7,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[3]),32);
            tracep->chgIData(oldp+8,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[4]),32);
            tracep->chgIData(oldp+9,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[5]),32);
            tracep->chgIData(oldp+10,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[6]),32);
            tracep->chgIData(oldp+11,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[7]),32);
            tracep->chgIData(oldp+12,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[8]),32);
            tracep->chgIData(oldp+13,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[9]),32);
            tracep->chgIData(oldp+14,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[10]),32);
            tracep->chgIData(oldp+15,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[11]),32);
            tracep->chgIData(oldp+16,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[12]),32);
            tracep->chgIData(oldp+17,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[13]),32);
            tracep->chgIData(oldp+18,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[14]),32);
            tracep->chgIData(oldp+19,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[15]),32);
            tracep->chgIData(oldp+20,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[16]),32);
            tracep->chgIData(oldp+21,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[17]),32);
            tracep->chgIData(oldp+22,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[18]),32);
            tracep->chgIData(oldp+23,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[19]),32);
            tracep->chgIData(oldp+24,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[20]),32);
            tracep->chgIData(oldp+25,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[21]),32);
            tracep->chgIData(oldp+26,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[22]),32);
            tracep->chgIData(oldp+27,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[23]),32);
            tracep->chgIData(oldp+28,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[24]),32);
            tracep->chgIData(oldp+29,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[25]),32);
            tracep->chgIData(oldp+30,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[26]),32);
            tracep->chgIData(oldp+31,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[27]),32);
            tracep->chgIData(oldp+32,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[28]),32);
            tracep->chgIData(oldp+33,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[29]),32);
            tracep->chgIData(oldp+34,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[30]),32);
            tracep->chgIData(oldp+35,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[31]),32);
        }
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[2U])) {
            tracep->chgCData(oldp+36,(vlTOPp->rv32__DOT__type4),3);
            tracep->chgBit(oldp+37,(vlTOPp->rv32__DOT__wen));
            tracep->chgBit(oldp+38,(vlTOPp->rv32__DOT__m1));
            tracep->chgBit(oldp+39,(vlTOPp->rv32__DOT__m2));
            tracep->chgBit(oldp+40,(vlTOPp->rv32__DOT__m3));
            tracep->chgBit(oldp+41,(vlTOPp->rv32__DOT__m4));
            tracep->chgCData(oldp+42,(vlTOPp->rv32__DOT__aluc),2);
            tracep->chgIData(oldp+43,(vlTOPp->rv32__DOT__result),32);
            tracep->chgIData(oldp+44,(vlTOPp->rv32__DOT__rin),32);
            tracep->chgIData(oldp+45,(vlTOPp->rv32__DOT__src1),32);
            tracep->chgIData(oldp+46,(((4U & (IData)(vlTOPp->rv32__DOT__type4))
                                        ? ((2U & (IData)(vlTOPp->rv32__DOT__type4))
                                            ? ((1U 
                                                & (IData)(vlTOPp->rv32__DOT__type4))
                                                ? 0U
                                                : vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32)
                                            : ((1U 
                                                & (IData)(vlTOPp->rv32__DOT__type4))
                                                ? vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32
                                                : vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32))
                                        : ((2U & (IData)(vlTOPp->rv32__DOT__type4))
                                            ? vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32
                                            : ((1U 
                                                & (IData)(vlTOPp->rv32__DOT__type4))
                                                ? vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32
                                                : 0U)))),32);
            tracep->chgIData(oldp+47,(vlTOPp->rv32__DOT__num1),32);
            tracep->chgIData(oldp+48,(vlTOPp->rv32__DOT__num2),32);
            tracep->chgIData(oldp+49,(vlTOPp->rv32__DOT__PC_inst__DOT__pc_temp),32);
            tracep->chgWData(oldp+50,(vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3),66);
            tracep->chgQData(oldp+53,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+55,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+57,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+58,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+59,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+60,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+61,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+62,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__hit));
            tracep->chgSData(oldp+63,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12),12);
            tracep->chgIData(oldp+64,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20),20);
            tracep->chgIData(oldp+65,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32),32);
            tracep->chgIData(oldp+66,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32),32);
            tracep->chgWData(oldp+67,(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3),66);
            tracep->chgQData(oldp+70,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+72,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+74,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+75,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+76,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+77,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+78,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+79,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit));
            tracep->chgWData(oldp+80,(vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3),66);
            tracep->chgQData(oldp+83,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+85,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+87,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+88,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+89,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+90,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+91,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+92,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__hit));
            tracep->chgWData(oldp+93,(vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3),66);
            tracep->chgQData(oldp+96,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+98,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+100,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+101,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+102,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+103,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+104,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+105,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit));
        }
        tracep->chgBit(oldp+106,(vlTOPp->clk));
        tracep->chgBit(oldp+107,(vlTOPp->rst));
        tracep->chgIData(oldp+108,(vlTOPp->inst),32);
        tracep->chgIData(oldp+109,(vlTOPp->pc),32);
        tracep->chgCData(oldp+110,((0x1fU & (vlTOPp->inst 
                                             >> 0xfU))),5);
        tracep->chgCData(oldp+111,((0x1fU & (vlTOPp->inst 
                                             >> 0x14U))),5);
        tracep->chgCData(oldp+112,((0x1fU & (vlTOPp->inst 
                                             >> 7U))),5);
        tracep->chgCData(oldp+113,((7U & (vlTOPp->inst 
                                          >> 0xcU))),3);
        tracep->chgCData(oldp+114,((0x7fU & (vlTOPp->inst 
                                             >> 0x19U))),7);
        tracep->chgIData(oldp+115,(((IData)(4U) + vlTOPp->pc)),32);
        tracep->chgIData(oldp+116,(((0U == (0x1fU & 
                                            (vlTOPp->inst 
                                             >> 0x14U)))
                                     ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                    [(0x1fU & (vlTOPp->inst 
                                               >> 0x14U))])),32);
        tracep->chgCData(oldp+117,((0x7fU & vlTOPp->inst)),7);
        tracep->chgBit(oldp+118,(((1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt)) 
                                  & (IData)(vlTOPp->rv32__DOT__wen))));
    }
}

void Vrv32::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vrv32__Syms* __restrict vlSymsp = static_cast<Vrv32__Syms*>(userp);
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
        vlTOPp->__Vm_traceActivity[1U] = 0U;
        vlTOPp->__Vm_traceActivity[2U] = 0U;
    }
}
