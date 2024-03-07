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
            tracep->chgCData(oldp+0,(vlTOPp->rv32__DOT__PC_inst__DOT__clk_div4),2);
            tracep->chgIData(oldp+1,(vlTOPp->rv32__DOT__register_file_inst__DOT__i),32);
            tracep->chgIData(oldp+2,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0]),32);
            tracep->chgIData(oldp+3,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[1]),32);
            tracep->chgIData(oldp+4,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[2]),32);
            tracep->chgIData(oldp+5,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[3]),32);
            tracep->chgIData(oldp+6,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[4]),32);
            tracep->chgIData(oldp+7,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[5]),32);
            tracep->chgIData(oldp+8,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[6]),32);
            tracep->chgIData(oldp+9,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[7]),32);
            tracep->chgIData(oldp+10,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[8]),32);
            tracep->chgIData(oldp+11,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[9]),32);
            tracep->chgIData(oldp+12,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[10]),32);
            tracep->chgIData(oldp+13,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[11]),32);
            tracep->chgIData(oldp+14,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[12]),32);
            tracep->chgIData(oldp+15,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[13]),32);
            tracep->chgIData(oldp+16,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[14]),32);
            tracep->chgIData(oldp+17,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[15]),32);
            tracep->chgIData(oldp+18,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[16]),32);
            tracep->chgIData(oldp+19,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[17]),32);
            tracep->chgIData(oldp+20,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[18]),32);
            tracep->chgIData(oldp+21,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[19]),32);
            tracep->chgIData(oldp+22,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[20]),32);
            tracep->chgIData(oldp+23,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[21]),32);
            tracep->chgIData(oldp+24,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[22]),32);
            tracep->chgIData(oldp+25,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[23]),32);
            tracep->chgIData(oldp+26,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[24]),32);
            tracep->chgIData(oldp+27,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[25]),32);
            tracep->chgIData(oldp+28,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[26]),32);
            tracep->chgIData(oldp+29,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[27]),32);
            tracep->chgIData(oldp+30,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[28]),32);
            tracep->chgIData(oldp+31,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[29]),32);
            tracep->chgIData(oldp+32,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[30]),32);
            tracep->chgIData(oldp+33,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[31]),32);
        }
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[2U])) {
            tracep->chgIData(oldp+34,(((0xfffff000U 
                                        & ((- (IData)(
                                                      (1U 
                                                       & ((IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12) 
                                                          >> 0xbU)))) 
                                           << 0xcU)) 
                                       | (IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12))),32);
            tracep->chgIData(oldp+35,(vlTOPp->rv32__DOT__num2),32);
            tracep->chgSData(oldp+36,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12),12);
            tracep->chgWData(oldp+37,(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3),66);
            tracep->chgQData(oldp+40,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+42,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+44,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+45,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+46,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+47,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+48,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+49,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit));
        }
        tracep->chgBit(oldp+50,(vlTOPp->clk));
        tracep->chgBit(oldp+51,(vlTOPp->rst));
        tracep->chgIData(oldp+52,(vlTOPp->inst),32);
        tracep->chgIData(oldp+53,(vlTOPp->pc),32);
        tracep->chgCData(oldp+54,((0x1fU & (vlTOPp->inst 
                                            >> 0xfU))),5);
        tracep->chgCData(oldp+55,((0x1fU & (vlTOPp->inst 
                                            >> 0x14U))),5);
        tracep->chgCData(oldp+56,((0x1fU & (vlTOPp->inst 
                                            >> 7U))),5);
        tracep->chgCData(oldp+57,((0x7fU & (vlTOPp->inst 
                                            >> 0x19U))),7);
        tracep->chgCData(oldp+58,(((0x13U == (0x7fU 
                                              & vlTOPp->inst))
                                    ? 2U : 0U)),3);
        tracep->chgIData(oldp+59,((((0U == (0x1fU & 
                                            (vlTOPp->inst 
                                             >> 0xfU)))
                                     ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                    [(0x1fU & (vlTOPp->inst 
                                               >> 0xfU))]) 
                                   + vlTOPp->rv32__DOT__num2)),32);
        tracep->chgIData(oldp+60,(((0U == (0x1fU & 
                                           (vlTOPp->inst 
                                            >> 0xfU)))
                                    ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                   [(0x1fU & (vlTOPp->inst 
                                              >> 0xfU))])),32);
        tracep->chgIData(oldp+61,(((0U == (0x1fU & 
                                           (vlTOPp->inst 
                                            >> 0x14U)))
                                    ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                   [(0x1fU & (vlTOPp->inst 
                                              >> 0x14U))])),32);
        tracep->chgCData(oldp+62,((0x7fU & vlTOPp->inst)),7);
        tracep->chgCData(oldp+63,((7U & (vlTOPp->inst 
                                         >> 0xcU))),3);
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
