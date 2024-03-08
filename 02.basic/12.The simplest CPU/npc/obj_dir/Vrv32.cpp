// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrv32.h for the primary calling header

#include "Vrv32.h"
#include "Vrv32__Syms.h"

//==========

VerilatedContext* Vrv32::contextp() {
    return __VlSymsp->_vm_contextp__;
}

void Vrv32::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vrv32::eval\n"); );
    Vrv32__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/uae/ysyx/ysyx-workbench/npc/vsrc/rv32.v", 34, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vrv32::_eval_initial_loop(Vrv32__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/uae/ysyx/ysyx-workbench/npc/vsrc/rv32.v", 34, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vrv32::_sequent__TOP__1(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_sequent__TOP__1\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*1:0*/ __Vdly__rv32__DOT__PC_inst__DOT__clk_div4;
    CData/*0:0*/ __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v0;
    CData/*4:0*/ __Vdlyvdim0__rv32__DOT__register_file_inst__DOT__regs__v32;
    CData/*0:0*/ __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v32;
    IData/*31:0*/ __Vdly__pc;
    IData/*31:0*/ __Vdlyvval__rv32__DOT__register_file_inst__DOT__regs__v32;
    // Body
    __Vdly__rv32__DOT__PC_inst__DOT__clk_div4 = vlTOPp->rv32__DOT__PC_inst__DOT__clk_div4;
    __Vdly__pc = vlTOPp->pc;
    if (vlTOPp->rst) {
        vlTOPp->rv32__DOT__register_file_inst__DOT__i = 0x20U;
    }
    __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v0 = 0U;
    __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v32 = 0U;
    __Vdly__rv32__DOT__PC_inst__DOT__clk_div4 = ((IData)(vlTOPp->rst)
                                                  ? 0U
                                                  : 
                                                 ((3U 
                                                   == (IData)(vlTOPp->rv32__DOT__PC_inst__DOT__clk_div4))
                                                   ? 0U
                                                   : 
                                                  (3U 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->rv32__DOT__PC_inst__DOT__clk_div4)))));
    if (vlTOPp->rst) {
        __Vdly__pc = 0x80000000U;
    } else {
        if ((0U == (IData)(vlTOPp->rv32__DOT__PC_inst__DOT__clk_div4))) {
            __Vdly__pc = ((IData)(4U) + vlTOPp->pc);
        }
    }
    if (vlTOPp->rst) {
        __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v0 = 1U;
    } else {
        __Vdlyvval__rv32__DOT__register_file_inst__DOT__regs__v32 
            = ((0U != (0x1fU & (vlTOPp->inst >> 7U)))
                ? vlTOPp->rv32__DOT__result : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
               [(0x1fU & (vlTOPp->inst >> 7U))]);
        __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v32 = 1U;
        __Vdlyvdim0__rv32__DOT__register_file_inst__DOT__regs__v32 
            = (0x1fU & (vlTOPp->inst >> 7U));
    }
    vlTOPp->pc = __Vdly__pc;
    vlTOPp->rv32__DOT__PC_inst__DOT__clk_div4 = __Vdly__rv32__DOT__PC_inst__DOT__clk_div4;
    if (__Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v0) {
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[1U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[2U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[3U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[4U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[5U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[6U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[7U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[8U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[9U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0xaU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0xbU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0xcU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0xdU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0xeU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0xfU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x10U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x11U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x12U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x13U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x14U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x15U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x16U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x17U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x18U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x19U] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x1aU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x1bU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x1cU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x1dU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x1eU] = 0U;
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[0x1fU] = 0U;
    }
    if (__Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v32) {
        vlTOPp->rv32__DOT__register_file_inst__DOT__regs[__Vdlyvdim0__rv32__DOT__register_file_inst__DOT__regs__v32] 
            = __Vdlyvval__rv32__DOT__register_file_inst__DOT__regs__v32;
    }
}

VL_INLINE_OPT void Vrv32::_combo__TOP__2(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_combo__TOP__2\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12 
        = ((1U == ((0x13U == (0x7fU & vlTOPp->inst))
                    ? 2U : 0U)) ? 0U : ((2U == ((0x13U 
                                                 == 
                                                 (0x7fU 
                                                  & vlTOPp->inst))
                                                 ? 2U
                                                 : 0U))
                                         ? (0xfffU 
                                            & (vlTOPp->inst 
                                               >> 0x14U))
                                         : 0U));
    vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[0U] 
        = (IData)((0x100000000ULL | (QData)((IData)(
                                                    ((0xfffff000U 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & ((IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12) 
                                                                        >> 0xbU)))) 
                                                         << 0xcU)) 
                                                     | (IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12))))));
    vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[1U] 
        = ((0xfffffffeU & ((IData)((QData)((IData)(
                                                   ((0U 
                                                     == 
                                                     (0x1fU 
                                                      & (vlTOPp->inst 
                                                         >> 0x14U)))
                                                     ? 0U
                                                     : 
                                                    vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                                    [
                                                    (0x1fU 
                                                     & (vlTOPp->inst 
                                                        >> 0x14U))])))) 
                           << 1U)) | (IData)(((0x100000000ULL 
                                               | (QData)((IData)(
                                                                 ((0xfffff000U 
                                                                   & ((- (IData)(
                                                                                (1U 
                                                                                & ((IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12) 
                                                                                >> 0xbU)))) 
                                                                      << 0xcU)) 
                                                                  | (IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12))))) 
                                              >> 0x20U)));
    vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[2U] 
        = ((1U & ((IData)((QData)((IData)(((0U == (0x1fU 
                                                   & (vlTOPp->inst 
                                                      >> 0x14U)))
                                            ? 0U : 
                                           vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                           [(0x1fU 
                                             & (vlTOPp->inst 
                                                >> 0x14U))])))) 
                  >> 0x1fU)) | (0xfffffffeU & ((IData)(
                                                       ((QData)((IData)(
                                                                        ((0U 
                                                                          == 
                                                                          (0x1fU 
                                                                           & (vlTOPp->inst 
                                                                              >> 0x14U)))
                                                                          ? 0U
                                                                          : 
                                                                         vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                                                         [
                                                                         (0x1fU 
                                                                          & (vlTOPp->inst 
                                                                             >> 0x14U))]))) 
                                                        >> 0x20U)) 
                                               << 1U)));
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[0U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[1U])) 
                              << 0x20U) | (QData)((IData)(
                                                          vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[0U]))));
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[1U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[2U])) 
                              << 0x1fU) | ((QData)((IData)(
                                                           vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[1U])) 
                                           >> 1U)));
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[0U] 
        = (IData)(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list
                  [0U]);
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list[1U] 
        = (IData)(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list
                  [1U]);
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[0U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list
                         [0U] >> 0x20U)));
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list[1U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list
                         [1U] >> 0x20U)));
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit = vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
        [0U];
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit) 
                                                | vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
                                                [1U]);
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out = 
        ((- (IData)(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
                    [0U])) & vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list
         [0U]);
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out = 
        (vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out 
         | ((- (IData)(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
                       [1U])) & vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list
            [1U]));
    vlTOPp->rv32__DOT__num2 = vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out;
    vlTOPp->rv32__DOT__result = (((0U == (0x1fU & (vlTOPp->inst 
                                                   >> 0xfU)))
                                   ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                                  [(0x1fU & (vlTOPp->inst 
                                             >> 0xfU))]) 
                                 + vlTOPp->rv32__DOT__num2);
}

void Vrv32::_eval(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_eval\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((IData)(vlTOPp->rst) & (~ (IData)(vlTOPp->__Vclklast__TOP__rst))))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
        vlTOPp->__Vm_traceActivity[1U] = 1U;
    }
    vlTOPp->_combo__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity[2U] = 1U;
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst = vlTOPp->rst;
}

VL_INLINE_OPT QData Vrv32::_change_request(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_change_request\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vrv32::_change_request_1(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_change_request_1\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vrv32::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG