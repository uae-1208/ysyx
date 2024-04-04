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
            tracep->chgBit(oldp+0,((0U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
            tracep->chgBit(oldp+1,((1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
            tracep->chgBit(oldp+2,((2U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
            tracep->chgIData(oldp+3,(vlTOPp->rv32__DOT__pc),32);
            tracep->chgIData(oldp+4,(((IData)(4U) + vlTOPp->rv32__DOT__pc)),32);
            tracep->chgCData(oldp+5,(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt),2);
            tracep->chgIData(oldp+6,(vlTOPp->rv32__DOT__pc_reg_inst__DOT__inst_reg),32);
            tracep->chgIData(oldp+7,(vlTOPp->rv32__DOT__register_file_inst__DOT__i),32);
            tracep->chgIData(oldp+8,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0]),32);
            tracep->chgIData(oldp+9,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[1]),32);
            tracep->chgIData(oldp+10,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[2]),32);
            tracep->chgIData(oldp+11,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[3]),32);
            tracep->chgIData(oldp+12,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[4]),32);
            tracep->chgIData(oldp+13,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[5]),32);
            tracep->chgIData(oldp+14,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[6]),32);
            tracep->chgIData(oldp+15,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[7]),32);
            tracep->chgIData(oldp+16,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[8]),32);
            tracep->chgIData(oldp+17,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[9]),32);
            tracep->chgIData(oldp+18,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[10]),32);
            tracep->chgIData(oldp+19,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[11]),32);
            tracep->chgIData(oldp+20,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[12]),32);
            tracep->chgIData(oldp+21,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[13]),32);
            tracep->chgIData(oldp+22,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[14]),32);
            tracep->chgIData(oldp+23,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[15]),32);
            tracep->chgIData(oldp+24,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[16]),32);
            tracep->chgIData(oldp+25,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[17]),32);
            tracep->chgIData(oldp+26,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[18]),32);
            tracep->chgIData(oldp+27,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[19]),32);
            tracep->chgIData(oldp+28,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[20]),32);
            tracep->chgIData(oldp+29,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[21]),32);
            tracep->chgIData(oldp+30,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[22]),32);
            tracep->chgIData(oldp+31,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[23]),32);
            tracep->chgIData(oldp+32,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[24]),32);
            tracep->chgIData(oldp+33,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[25]),32);
            tracep->chgIData(oldp+34,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[26]),32);
            tracep->chgIData(oldp+35,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[27]),32);
            tracep->chgIData(oldp+36,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[28]),32);
            tracep->chgIData(oldp+37,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[29]),32);
            tracep->chgIData(oldp+38,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[30]),32);
            tracep->chgIData(oldp+39,(vlTOPp->rv32__DOT__register_file_inst__DOT__regs[31]),32);
        }
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[2U])) {
            tracep->chgCData(oldp+40,((0x1fU & (vlTOPp->rv32__DOT__inst 
                                                >> 0xfU))),5);
            tracep->chgCData(oldp+41,((0x1fU & (vlTOPp->rv32__DOT__inst 
                                                >> 0x14U))),5);
            tracep->chgCData(oldp+42,((0x1fU & (vlTOPp->rv32__DOT__inst 
                                                >> 7U))),5);
            tracep->chgCData(oldp+43,((7U & (vlTOPp->rv32__DOT__inst 
                                             >> 0xcU))),3);
            tracep->chgCData(oldp+44,((0x7fU & (vlTOPp->rv32__DOT__inst 
                                                >> 0x19U))),7);
            tracep->chgIData(oldp+45,(vlTOPp->rv32__DOT__inst),32);
            tracep->chgCData(oldp+46,(vlTOPp->rv32__DOT__type4),3);
            tracep->chgBit(oldp+47,(vlTOPp->rv32__DOT__wen_reg));
            tracep->chgBit(oldp+48,(vlTOPp->rv32__DOT__wen_mem));
            tracep->chgCData(oldp+49,(vlTOPp->rv32__DOT__wmask),8);
            tracep->chgCData(oldp+50,(vlTOPp->rv32__DOT__rmask),3);
            tracep->chgBit(oldp+51,(vlTOPp->rv32__DOT__m1));
            tracep->chgBit(oldp+52,(vlTOPp->rv32__DOT__m2));
            tracep->chgBit(oldp+53,(vlTOPp->rv32__DOT__m3));
            tracep->chgCData(oldp+54,(vlTOPp->rv32__DOT__m4),2);
            tracep->chgBit(oldp+55,(vlTOPp->rv32__DOT__m5));
            tracep->chgBit(oldp+56,(vlTOPp->rv32__DOT__m6));
            tracep->chgCData(oldp+57,(vlTOPp->rv32__DOT__aluc),5);
            tracep->chgIData(oldp+58,(vlTOPp->rv32__DOT__result),32);
            tracep->chgIData(oldp+59,(vlTOPp->rv32__DOT__rin),32);
            tracep->chgIData(oldp+60,(vlTOPp->rv32__DOT__src1),32);
            tracep->chgIData(oldp+61,(vlTOPp->rv32__DOT__src2),32);
            tracep->chgIData(oldp+62,(vlTOPp->rv32__DOT__imm),32);
            tracep->chgIData(oldp+63,(vlTOPp->rv32__DOT__num1),32);
            tracep->chgIData(oldp+64,(vlTOPp->rv32__DOT__num2),32);
            tracep->chgIData(oldp+65,(vlTOPp->rv32__DOT__raddr),32);
            tracep->chgIData(oldp+66,(vlTOPp->rv32__DOT__mem_rdata),32);
            tracep->chgIData(oldp+67,(vlTOPp->rv32__DOT__PC_inst__DOT__pc_temp1),32);
            tracep->chgIData(oldp+68,(vlTOPp->rv32__DOT__PC_inst__DOT__pc_temp2),32);
            tracep->chgWData(oldp+69,(vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3),66);
            tracep->chgQData(oldp+72,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+74,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+76,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+77,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+78,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+79,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+80,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+81,(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__hit));
            tracep->chgBit(oldp+82,(vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i6____pinNumber2));
            tracep->chgWData(oldp+83,(vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i6____pinNumber3),66);
            tracep->chgQData(oldp+86,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+88,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+90,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+91,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+92,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+93,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+94,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+95,(vlTOPp->rv32__DOT__PC_inst__DOT__i6__DOT__i0__DOT__hit));
            tracep->chgBit(oldp+96,(vlTOPp->rv32__DOT____Vcellinp__mem_inst__wen_mem));
            tracep->chgCData(oldp+97,(vlTOPp->rv32__DOT____Vcellinp__mem_inst__rmask),3);
            tracep->chgIData(oldp+98,(vlTOPp->rv32__DOT__mem_inst__DOT__rdata_temp),32);
            tracep->chgCData(oldp+99,((0x7fU & vlTOPp->rv32__DOT__inst)),7);
            tracep->chgSData(oldp+100,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12),12);
            tracep->chgIData(oldp+101,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20),20);
            tracep->chgIData(oldp+102,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32),32);
            tracep->chgIData(oldp+103,(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32),32);
            tracep->chgWData(oldp+104,(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3),66);
            tracep->chgQData(oldp+107,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+109,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+111,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+112,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+113,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+114,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+115,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+116,(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit));
            tracep->chgWData(oldp+117,(vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3),66);
            tracep->chgQData(oldp+120,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+122,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+124,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+125,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+126,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+127,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+128,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+129,(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__hit));
            tracep->chgWData(oldp+130,(vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3),136);
            tracep->chgQData(oldp+135,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[0]),34);
            tracep->chgQData(oldp+137,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[1]),34);
            tracep->chgQData(oldp+139,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[2]),34);
            tracep->chgQData(oldp+141,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[3]),34);
            tracep->chgCData(oldp+143,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[0]),2);
            tracep->chgCData(oldp+144,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[1]),2);
            tracep->chgCData(oldp+145,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[2]),2);
            tracep->chgCData(oldp+146,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[3]),2);
            tracep->chgIData(oldp+147,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+148,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+149,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[2]),32);
            tracep->chgIData(oldp+150,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[3]),32);
            tracep->chgIData(oldp+151,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+152,(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit));
            tracep->chgBit(oldp+153,(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber2));
            tracep->chgWData(oldp+154,(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3),66);
            tracep->chgQData(oldp+157,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list[0]),33);
            tracep->chgQData(oldp+159,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list[1]),33);
            tracep->chgBit(oldp+161,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list[0]));
            tracep->chgBit(oldp+162,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list[1]));
            tracep->chgIData(oldp+163,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list[0]),32);
            tracep->chgIData(oldp+164,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list[1]),32);
            tracep->chgIData(oldp+165,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__lut_out),32);
            tracep->chgBit(oldp+166,(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__hit));
            tracep->chgIData(oldp+167,(((IData)(1U) 
                                        + (~ vlTOPp->rv32__DOT__num2))),32);
            tracep->chgIData(oldp+168,((0x1fU & vlTOPp->rv32__DOT__num2)),32);
        }
        tracep->chgBit(oldp+169,(vlTOPp->clk));
        tracep->chgBit(oldp+170,(vlTOPp->rst));
        tracep->chgIData(oldp+171,((vlTOPp->rv32__DOT__pc 
                                    + vlTOPp->rv32__DOT__imm)),32);
        tracep->chgBit(oldp+172,(((IData)(vlTOPp->rv32__DOT__wen_reg) 
                                  & (1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt)))));
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
