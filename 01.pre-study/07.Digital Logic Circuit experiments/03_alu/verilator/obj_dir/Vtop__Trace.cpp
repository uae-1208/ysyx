// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vtop::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[1U])) {
            tracep->chgCData(oldp+0,(vlTOPp->top__DOT__a_s),4);
            tracep->chgBit(oldp+1,(vlTOPp->top__DOT__a_cin));
            tracep->chgCData(oldp+2,(vlTOPp->top__DOT__B),4);
            tracep->chgBit(oldp+3,(vlTOPp->top__DOT__overflow_temp));
        }
        tracep->chgCData(oldp+4,(vlTOPp->A),4);
        tracep->chgCData(oldp+5,(vlTOPp->b),4);
        tracep->chgCData(oldp+6,(vlTOPp->option),3);
        tracep->chgBit(oldp+7,(vlTOPp->carry));
        tracep->chgBit(oldp+8,(vlTOPp->overflow));
        tracep->chgBit(oldp+9,(vlTOPp->zero));
        tracep->chgCData(oldp+10,(vlTOPp->result),4);
        tracep->chgCData(oldp+11,((0xfU & ((IData)(1U) 
                                           + (~ (IData)(vlTOPp->b))))),4);
    }
}

void Vtop::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
        vlTOPp->__Vm_traceActivity[1U] = 0U;
    }
}
