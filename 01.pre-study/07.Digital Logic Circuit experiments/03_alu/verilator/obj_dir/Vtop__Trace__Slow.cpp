// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


//======================

void Vtop::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vtop::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vtop::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vtop::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vtop::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+5,"A", false,-1, 3,0);
        tracep->declBus(c+6,"b", false,-1, 3,0);
        tracep->declBus(c+7,"option", false,-1, 2,0);
        tracep->declBit(c+8,"carry", false,-1);
        tracep->declBit(c+9,"overflow", false,-1);
        tracep->declBit(c+10,"zero", false,-1);
        tracep->declBus(c+11,"result", false,-1, 3,0);
        tracep->declBus(c+5,"top A", false,-1, 3,0);
        tracep->declBus(c+6,"top b", false,-1, 3,0);
        tracep->declBus(c+7,"top option", false,-1, 2,0);
        tracep->declBit(c+8,"top carry", false,-1);
        tracep->declBit(c+9,"top overflow", false,-1);
        tracep->declBit(c+10,"top zero", false,-1);
        tracep->declBus(c+11,"top result", false,-1, 3,0);
        tracep->declBus(c+1,"top a_s", false,-1, 3,0);
        tracep->declBit(c+2,"top a_cin", false,-1);
        tracep->declBus(c+3,"top B", false,-1, 3,0);
        tracep->declBit(c+4,"top overflow_temp", false,-1);
        tracep->declBus(c+6,"top complement_inst b", false,-1, 3,0);
        tracep->declBus(c+7,"top complement_inst option", false,-1, 2,0);
        tracep->declBus(c+3,"top complement_inst B", false,-1, 3,0);
        tracep->declBus(c+12,"top complement_inst temp", false,-1, 3,0);
    }
}

void Vtop::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vtop::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vtop::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vtop__Syms* __restrict vlSymsp = static_cast<Vtop__Syms*>(userp);
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlTOPp->top__DOT__a_s),4);
        tracep->fullBit(oldp+2,(vlTOPp->top__DOT__a_cin));
        tracep->fullCData(oldp+3,(vlTOPp->top__DOT__B),4);
        tracep->fullBit(oldp+4,(vlTOPp->top__DOT__overflow_temp));
        tracep->fullCData(oldp+5,(vlTOPp->A),4);
        tracep->fullCData(oldp+6,(vlTOPp->b),4);
        tracep->fullCData(oldp+7,(vlTOPp->option),3);
        tracep->fullBit(oldp+8,(vlTOPp->carry));
        tracep->fullBit(oldp+9,(vlTOPp->overflow));
        tracep->fullBit(oldp+10,(vlTOPp->zero));
        tracep->fullCData(oldp+11,(vlTOPp->result),4);
        tracep->fullCData(oldp+12,((0xfU & ((IData)(1U) 
                                            + (~ (IData)(vlTOPp->b))))),4);
    }
}
