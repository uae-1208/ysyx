// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrv32.h for the primary calling header

#include "Vrv32.h"
#include "Vrv32__Syms.h"

#include "verilated_dpi.h"

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
            VL_FATAL_MT("/home/uae/ysyx/ysyx-workbench/npc/vsrc/rv32.v", 94, "",
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
            VL_FATAL_MT("/home/uae/ysyx/ysyx-workbench/npc/vsrc/rv32.v", 94, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vrv32::__Vdpiimwrap_rv32__DOT__mem_inst__DOT__pmem_read_TOP(IData/*31:0*/ raddr, IData/*31:0*/ (&pmem_read__Vfuncrtn)) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::__Vdpiimwrap_rv32__DOT__mem_inst__DOT__pmem_read_TOP\n"); );
    // Body
    int raddr__Vcvt;
    for (size_t raddr__Vidx = 0; raddr__Vidx < 1; ++raddr__Vidx) raddr__Vcvt = raddr;
    int pmem_read__Vfuncrtn__Vcvt;
    pmem_read__Vfuncrtn__Vcvt = pmem_read(raddr__Vcvt);
    pmem_read__Vfuncrtn = pmem_read__Vfuncrtn__Vcvt;
}

VL_INLINE_OPT void Vrv32::__Vdpiimwrap_rv32__DOT__mem_inst__DOT__pmem_write_TOP(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::__Vdpiimwrap_rv32__DOT__mem_inst__DOT__pmem_write_TOP\n"); );
    // Body
    int waddr__Vcvt;
    for (size_t waddr__Vidx = 0; waddr__Vidx < 1; ++waddr__Vidx) waddr__Vcvt = waddr;
    int wdata__Vcvt;
    for (size_t wdata__Vidx = 0; wdata__Vidx < 1; ++wdata__Vidx) wdata__Vcvt = wdata;
    char wmask__Vcvt;
    for (size_t wmask__Vidx = 0; wmask__Vidx < 1; ++wmask__Vidx) wmask__Vcvt = wmask;
    pmem_write(waddr__Vcvt, wdata__Vcvt, wmask__Vcvt);
}

VL_INLINE_OPT void Vrv32::__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(IData/*31:0*/ station, IData/*31:0*/ inst, CData/*7:0*/ unit) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP\n"); );
    // Body
    int station__Vcvt;
    for (size_t station__Vidx = 0; station__Vidx < 1; ++station__Vidx) station__Vcvt = station;
    int inst__Vcvt;
    for (size_t inst__Vidx = 0; inst__Vidx < 1; ++inst__Vidx) inst__Vcvt = inst;
    char unit__Vcvt;
    for (size_t unit__Vidx = 0; unit__Vidx < 1; ++unit__Vidx) unit__Vcvt = unit;
    ebreak(station__Vcvt, inst__Vcvt, unit__Vcvt);
}

VL_INLINE_OPT void Vrv32::_sequent__TOP__1(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_sequent__TOP__1\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*1:0*/ __Vdly__rv32__DOT__clk_count_inst__DOT__clk_cnt;
    CData/*0:0*/ __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v0;
    CData/*4:0*/ __Vdlyvdim0__rv32__DOT__register_file_inst__DOT__regs__v32;
    CData/*0:0*/ __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v32;
    IData/*31:0*/ __Vdlyvval__rv32__DOT__register_file_inst__DOT__regs__v32;
    // Body
    __Vdly__rv32__DOT__clk_count_inst__DOT__clk_cnt 
        = vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt;
    __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v0 = 0U;
    __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v32 = 0U;
    if (vlTOPp->rst) {
        vlTOPp->rv32__DOT__register_file_inst__DOT__i = 0x20U;
    }
    if (vlTOPp->rst) {
        vlTOPp->rv32__DOT__pc = 0x80000000U;
    } else {
        if ((2U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))) {
            vlTOPp->rv32__DOT__pc = vlTOPp->rv32__DOT__PC_inst__DOT__pc_temp;
        }
    }
    if (vlTOPp->rst) {
        __Vdly__rv32__DOT__clk_count_inst__DOT__clk_cnt = 0U;
        vlTOPp->rv32__DOT__pc_reg_inst__DOT__inst_reg 
            = vlTOPp->rv32__DOT__mem_rdata;
    } else {
        __Vdly__rv32__DOT__clk_count_inst__DOT__clk_cnt 
            = ((2U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))
                ? 0U : (3U & ((IData)(1U) + (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
        vlTOPp->rv32__DOT__pc_reg_inst__DOT__inst_reg 
            = ((2U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))
                ? vlTOPp->rv32__DOT__mem_rdata : vlTOPp->rv32__DOT__inst);
    }
    if (vlTOPp->rst) {
        __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v0 = 1U;
    } else {
        __Vdlyvval__rv32__DOT__register_file_inst__DOT__regs__v32 
            = ((((IData)(vlTOPp->rv32__DOT__wen_r) 
                 & (1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))) 
                & (0U != (0x1fU & (vlTOPp->rv32__DOT__inst 
                                   >> 7U)))) ? vlTOPp->rv32__DOT__rin
                : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
               [(0x1fU & (vlTOPp->rv32__DOT__inst >> 7U))]);
        __Vdlyvset__rv32__DOT__register_file_inst__DOT__regs__v32 = 1U;
        __Vdlyvdim0__rv32__DOT__register_file_inst__DOT__regs__v32 
            = (0x1fU & (vlTOPp->rv32__DOT__inst >> 7U));
    }
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
    vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt 
        = __Vdly__rv32__DOT__clk_count_inst__DOT__clk_cnt;
}

VL_INLINE_OPT void Vrv32::_settle__TOP__2(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_settle__TOP__2\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->rv32__DOT__inst = ((0U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))
                                ? vlTOPp->rv32__DOT__mem_rdata
                                : vlTOPp->rv32__DOT__pc_reg_inst__DOT__inst_reg);
    vlTOPp->rv32__DOT__src2 = ((0U == (0x1fU & (vlTOPp->rv32__DOT__inst 
                                                >> 0x14U)))
                                ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                               [(0x1fU & (vlTOPp->rv32__DOT__inst 
                                          >> 0x14U))]);
    vlTOPp->rv32__DOT__src1 = ((0U == (0x1fU & (vlTOPp->rv32__DOT__inst 
                                                >> 0xfU)))
                                ? 0U : vlTOPp->rv32__DOT__register_file_inst__DOT__regs
                               [(0x1fU & (vlTOPp->rv32__DOT__inst 
                                          >> 0xfU))]);
    if ((0x40U & vlTOPp->rv32__DOT__inst)) {
        if ((0x20U & vlTOPp->rv32__DOT__inst)) {
            if ((0x10U & vlTOPp->rv32__DOT__inst)) {
                if ((8U & vlTOPp->rv32__DOT__inst)) {
                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                } else {
                    if ((4U & vlTOPp->rv32__DOT__inst)) {
                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                    } else {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                if ((1U == (0xfffU 
                                            & (vlTOPp->rv32__DOT__inst 
                                               >> 0x14U)))) {
                                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(1U, vlTOPp->rv32__DOT__inst, 2U);
                                } else {
                                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                                }
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    }
                }
            } else {
                if ((8U & vlTOPp->rv32__DOT__inst)) {
                    if ((4U & vlTOPp->rv32__DOT__inst)) {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                vlTOPp->rv32__DOT__type4 = 6U;
                                vlTOPp->rv32__DOT__wen_r = 1U;
                                vlTOPp->rv32__DOT__wen_m = 0U;
                                vlTOPp->rv32__DOT__wmask = 0xfU;
                                vlTOPp->rv32__DOT__m1 = 0U;
                                vlTOPp->rv32__DOT__m2 = 1U;
                                vlTOPp->rv32__DOT__m3 = 1U;
                                vlTOPp->rv32__DOT__m4 = 0U;
                                vlTOPp->rv32__DOT__aluc = 1U;
                                vlTOPp->rv32__DOT__m5 = 0U;
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    } else {
                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                    }
                } else {
                    if ((4U & vlTOPp->rv32__DOT__inst)) {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                vlTOPp->rv32__DOT__type4 = 2U;
                                vlTOPp->rv32__DOT__wen_r = 1U;
                                vlTOPp->rv32__DOT__wen_m = 0U;
                                vlTOPp->rv32__DOT__wmask = 0xfU;
                                vlTOPp->rv32__DOT__m1 = 1U;
                                vlTOPp->rv32__DOT__m2 = 1U;
                                vlTOPp->rv32__DOT__m3 = 1U;
                                vlTOPp->rv32__DOT__m4 = 0U;
                                vlTOPp->rv32__DOT__m5 = 0U;
                                vlTOPp->rv32__DOT__aluc = 3U;
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    } else {
                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                    }
                }
            }
        } else {
            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
        }
    } else {
        if ((0x20U & vlTOPp->rv32__DOT__inst)) {
            if ((0x10U & vlTOPp->rv32__DOT__inst)) {
                if ((8U & vlTOPp->rv32__DOT__inst)) {
                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                } else {
                    if ((4U & vlTOPp->rv32__DOT__inst)) {
                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                    } else {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                vlTOPp->rv32__DOT__type4 = 1U;
                                vlTOPp->rv32__DOT__wen_r = 0U;
                                vlTOPp->rv32__DOT__wen_m = 0U;
                                vlTOPp->rv32__DOT__wmask = 0xfU;
                                vlTOPp->rv32__DOT__m1 = 1U;
                                vlTOPp->rv32__DOT__m2 = 0U;
                                vlTOPp->rv32__DOT__m3 = 0U;
                                vlTOPp->rv32__DOT__m4 = 1U;
                                vlTOPp->rv32__DOT__m5 = 0U;
                                if ((0U == (0x7fU & 
                                            (vlTOPp->rv32__DOT__inst 
                                             >> 0x19U)))) {
                                    if ((0U == (7U 
                                                & (vlTOPp->rv32__DOT__inst 
                                                   >> 0xcU)))) {
                                        vlTOPp->rv32__DOT__aluc = 1U;
                                    } else {
                                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                                    }
                                } else {
                                    if ((0x20U == (0x7fU 
                                                   & (vlTOPp->rv32__DOT__inst 
                                                      >> 0x19U)))) {
                                        if ((0U == 
                                             (7U & 
                                              (vlTOPp->rv32__DOT__inst 
                                               >> 0xcU)))) {
                                            vlTOPp->rv32__DOT__aluc = 2U;
                                        } else {
                                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                                        }
                                    } else {
                                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                                    }
                                }
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    }
                }
            } else {
                if ((8U & vlTOPp->rv32__DOT__inst)) {
                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                } else {
                    if ((4U & vlTOPp->rv32__DOT__inst)) {
                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                    } else {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                vlTOPp->rv32__DOT__type4 = 3U;
                                vlTOPp->rv32__DOT__wen_r = 0U;
                                vlTOPp->rv32__DOT__wen_m = 1U;
                                vlTOPp->rv32__DOT__wmask = 0xfU;
                                vlTOPp->rv32__DOT__m1 = 1U;
                                vlTOPp->rv32__DOT__m2 = 1U;
                                vlTOPp->rv32__DOT__m3 = 0U;
                                vlTOPp->rv32__DOT__m4 = 1U;
                                vlTOPp->rv32__DOT__m5 = 0U;
                                if ((2U == (7U & (vlTOPp->rv32__DOT__inst 
                                                  >> 0xcU)))) {
                                    vlTOPp->rv32__DOT__aluc = 1U;
                                } else {
                                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                                }
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    }
                }
            }
        } else {
            if ((0x10U & vlTOPp->rv32__DOT__inst)) {
                if ((8U & vlTOPp->rv32__DOT__inst)) {
                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                } else {
                    if ((4U & vlTOPp->rv32__DOT__inst)) {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                vlTOPp->rv32__DOT__type4 = 4U;
                                vlTOPp->rv32__DOT__wen_r = 1U;
                                vlTOPp->rv32__DOT__wen_m = 0U;
                                vlTOPp->rv32__DOT__wmask = 0xfU;
                                vlTOPp->rv32__DOT__m1 = 0U;
                                vlTOPp->rv32__DOT__m2 = 1U;
                                vlTOPp->rv32__DOT__m3 = 0U;
                                vlTOPp->rv32__DOT__m4 = 1U;
                                vlTOPp->rv32__DOT__m5 = 0U;
                                vlTOPp->rv32__DOT__aluc = 1U;
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    } else {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                vlTOPp->rv32__DOT__type4 = 2U;
                                vlTOPp->rv32__DOT__wen_r = 1U;
                                vlTOPp->rv32__DOT__wen_m = 0U;
                                vlTOPp->rv32__DOT__wmask = 0xfU;
                                vlTOPp->rv32__DOT__m1 = 1U;
                                vlTOPp->rv32__DOT__m2 = 1U;
                                vlTOPp->rv32__DOT__m3 = 0U;
                                vlTOPp->rv32__DOT__m4 = 1U;
                                vlTOPp->rv32__DOT__m5 = 0U;
                                if ((0U == (7U & (vlTOPp->rv32__DOT__inst 
                                                  >> 0xcU)))) {
                                    vlTOPp->rv32__DOT__aluc = 1U;
                                } else {
                                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                                }
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    }
                }
            } else {
                if ((8U & vlTOPp->rv32__DOT__inst)) {
                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                } else {
                    if ((4U & vlTOPp->rv32__DOT__inst)) {
                        vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                    } else {
                        if ((2U & vlTOPp->rv32__DOT__inst)) {
                            if ((1U & vlTOPp->rv32__DOT__inst)) {
                                vlTOPp->rv32__DOT__type4 = 2U;
                                vlTOPp->rv32__DOT__wen_r = 1U;
                                vlTOPp->rv32__DOT__wen_m = 0U;
                                vlTOPp->rv32__DOT__wmask = 0xfU;
                                vlTOPp->rv32__DOT__m1 = 1U;
                                vlTOPp->rv32__DOT__m2 = 1U;
                                vlTOPp->rv32__DOT__m3 = 0U;
                                vlTOPp->rv32__DOT__m4 = 2U;
                                vlTOPp->rv32__DOT__m5 = 1U;
                                if ((2U == (7U & (vlTOPp->rv32__DOT__inst 
                                                  >> 0xcU)))) {
                                    vlTOPp->rv32__DOT__aluc = 1U;
                                } else {
                                    vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                                }
                            } else {
                                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                            }
                        } else {
                            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, vlTOPp->rv32__DOT__inst, 2U);
                        }
                    }
                }
            }
        }
    }
    vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[0U] 
        = (IData)((0x100000000ULL | (QData)((IData)(vlTOPp->rv32__DOT__src1))));
    vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[1U] 
        = ((0xfffffffeU & ((IData)((QData)((IData)(vlTOPp->rv32__DOT__pc))) 
                           << 1U)) | (IData)(((0x100000000ULL 
                                               | (QData)((IData)(vlTOPp->rv32__DOT__src1))) 
                                              >> 0x20U)));
    vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[2U] 
        = ((1U & ((IData)((QData)((IData)(vlTOPp->rv32__DOT__pc))) 
                  >> 0x1fU)) | (0xfffffffeU & ((IData)(
                                                       ((QData)((IData)(vlTOPp->rv32__DOT__pc)) 
                                                        >> 0x20U)) 
                                               << 1U)));
    vlTOPp->rv32__DOT____Vcellinp__mem_inst__wen_m 
        = (((IData)(vlTOPp->rv32__DOT__wen_m) & (1U 
                                                 == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt))) 
           & (IData)(vlTOPp->clk));
    vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber2 
        = ((1U == (IData)(vlTOPp->rv32__DOT__clk_count_inst__DOT__clk_cnt)) 
           & (IData)(vlTOPp->rv32__DOT__m5));
    if ((4U & (IData)(vlTOPp->rv32__DOT__type4))) {
        if ((1U & (IData)(vlTOPp->rv32__DOT__type4))) {
            vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12 = 0U;
            vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, 0xdeafbeafU, 3U);
        } else {
            vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12 = 0U;
        }
    } else {
        if ((2U & (IData)(vlTOPp->rv32__DOT__type4))) {
            vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12 
                = (0xfffU & ((1U & (IData)(vlTOPp->rv32__DOT__type4))
                              ? ((0xfe0U & (vlTOPp->rv32__DOT__inst 
                                            >> 0x14U)) 
                                 | (0x1fU & (vlTOPp->rv32__DOT__inst 
                                             >> 7U)))
                              : (vlTOPp->rv32__DOT__inst 
                                 >> 0x14U)));
        } else {
            if ((1U & (IData)(vlTOPp->rv32__DOT__type4))) {
                vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12 = 0U;
            } else {
                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, 0xdeafbeafU, 3U);
                vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12 = 0U;
            }
        }
    }
    if ((4U & (IData)(vlTOPp->rv32__DOT__type4))) {
        if ((2U & (IData)(vlTOPp->rv32__DOT__type4))) {
            if ((1U & (IData)(vlTOPp->rv32__DOT__type4))) {
                vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20 = 0U;
                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, 0xdeafbeafU, 3U);
            } else {
                vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20 
                    = (0xfffffU & ((0x100000U & (vlTOPp->rv32__DOT__inst 
                                                 >> 0xbU)) 
                                   | ((0xf8000U & vlTOPp->rv32__DOT__inst) 
                                      | ((0x7000U & vlTOPp->rv32__DOT__inst) 
                                         | ((0x800U 
                                             & (vlTOPp->rv32__DOT__inst 
                                                >> 9U)) 
                                            | (0x7feU 
                                               & (vlTOPp->rv32__DOT__inst 
                                                  >> 0x14U)))))));
            }
        } else {
            vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20 
                = ((1U & (IData)(vlTOPp->rv32__DOT__type4))
                    ? 0U : (0xff000U & vlTOPp->rv32__DOT__inst));
        }
    } else {
        if ((2U & (IData)(vlTOPp->rv32__DOT__type4))) {
            vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20 = 0U;
        } else {
            if ((1U & (IData)(vlTOPp->rv32__DOT__type4))) {
                vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20 = 0U;
            } else {
                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, 0xdeafbeafU, 3U);
                vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20 = 0U;
            }
        }
    }
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[0U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[1U])) 
                              << 0x20U) | (QData)((IData)(
                                                          vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[0U]))));
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__pair_list[1U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[2U])) 
                              << 0x1fU) | ((QData)((IData)(
                                                           vlTOPp->rv32__DOT____Vcellinp__i1____pinNumber3[1U])) 
                                           >> 1U)));
    vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32 
        = ((0xfffff000U & ((- (IData)((1U & ((IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12) 
                                             >> 0xbU)))) 
                           << 0xcU)) | (IData)(vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12));
    vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32 
        = ((0xfff00000U & ((- (IData)((1U & (vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20 
                                             >> 0x13U)))) 
                           << 0x14U)) | vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20);
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
    if ((4U & (IData)(vlTOPp->rv32__DOT__type4))) {
        if ((2U & (IData)(vlTOPp->rv32__DOT__type4))) {
            if ((1U & (IData)(vlTOPp->rv32__DOT__type4))) {
                vlTOPp->rv32__DOT__imm = 0U;
                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, 0xdeafbeafU, 3U);
            } else {
                vlTOPp->rv32__DOT__imm = vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32;
            }
        } else {
            vlTOPp->rv32__DOT__imm = ((1U & (IData)(vlTOPp->rv32__DOT__type4))
                                       ? vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32
                                       : vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_20_to_32);
        }
    } else {
        if ((2U & (IData)(vlTOPp->rv32__DOT__type4))) {
            vlTOPp->rv32__DOT__imm = vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32;
        } else {
            if ((1U & (IData)(vlTOPp->rv32__DOT__type4))) {
                vlTOPp->rv32__DOT__imm = vlTOPp->rv32__DOT__imm_extend_inst__DOT__imm_12_to_32;
            } else {
                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, 0xdeafbeafU, 3U);
                vlTOPp->rv32__DOT__imm = 0U;
            }
        }
    }
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__m1) 
                                                == 
                                                vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
                                                [0U]);
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__i1__DOT__i0__DOT__hit) 
                                                | ((IData)(vlTOPp->rv32__DOT__m1) 
                                                   == 
                                                   vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
                                                   [1U]));
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out = 
        ((- (IData)(((IData)(vlTOPp->rv32__DOT__m1) 
                     == vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
                     [0U]))) & vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list
         [0U]);
    vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out = 
        (vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out 
         | ((- (IData)(((IData)(vlTOPp->rv32__DOT__m1) 
                        == vlTOPp->rv32__DOT__i1__DOT__i0__DOT__key_list
                        [1U]))) & vlTOPp->rv32__DOT__i1__DOT__i0__DOT__data_list
            [1U]));
    vlTOPp->rv32__DOT__num1 = vlTOPp->rv32__DOT__i1__DOT__i0__DOT__lut_out;
    vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3[0U] 
        = (IData)((0x100000000ULL | (QData)((IData)(vlTOPp->rv32__DOT__imm))));
    vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3[1U] 
        = ((0xfffffffeU & ((IData)((QData)((IData)(vlTOPp->rv32__DOT__src2))) 
                           << 1U)) | (IData)(((0x100000000ULL 
                                               | (QData)((IData)(vlTOPp->rv32__DOT__imm))) 
                                              >> 0x20U)));
    vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3[2U] 
        = ((1U & ((IData)((QData)((IData)(vlTOPp->rv32__DOT__src2))) 
                  >> 0x1fU)) | (0xfffffffeU & ((IData)(
                                                       ((QData)((IData)(vlTOPp->rv32__DOT__src2)) 
                                                        >> 0x20U)) 
                                               << 1U)));
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[0U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3[1U])) 
                              << 0x20U) | (QData)((IData)(
                                                          vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3[0U]))));
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list[1U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3[2U])) 
                              << 0x1fU) | ((QData)((IData)(
                                                           vlTOPp->rv32__DOT____Vcellinp__i2____pinNumber3[1U])) 
                                           >> 1U)));
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[0U] 
        = (IData)(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list
                  [0U]);
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list[1U] 
        = (IData)(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list
                  [1U]);
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[0U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list
                         [0U] >> 0x20U)));
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list[1U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__i2__DOT__i0__DOT__pair_list
                         [1U] >> 0x20U)));
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__m2) 
                                                == 
                                                vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list
                                                [0U]);
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__i2__DOT__i0__DOT__hit) 
                                                | ((IData)(vlTOPp->rv32__DOT__m2) 
                                                   == 
                                                   vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list
                                                   [1U]));
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__lut_out = 
        ((- (IData)(((IData)(vlTOPp->rv32__DOT__m2) 
                     == vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list
                     [0U]))) & vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list
         [0U]);
    vlTOPp->rv32__DOT__i2__DOT__i0__DOT__lut_out = 
        (vlTOPp->rv32__DOT__i2__DOT__i0__DOT__lut_out 
         | ((- (IData)(((IData)(vlTOPp->rv32__DOT__m2) 
                        == vlTOPp->rv32__DOT__i2__DOT__i0__DOT__key_list
                        [1U]))) & vlTOPp->rv32__DOT__i2__DOT__i0__DOT__data_list
            [1U]));
    vlTOPp->rv32__DOT__num2 = vlTOPp->rv32__DOT__i2__DOT__i0__DOT__lut_out;
    if ((1U == (IData)(vlTOPp->rv32__DOT__aluc))) {
        vlTOPp->rv32__DOT__result = (vlTOPp->rv32__DOT__num1 
                                     + vlTOPp->rv32__DOT__num2);
    } else {
        if ((2U == (IData)(vlTOPp->rv32__DOT__aluc))) {
            vlTOPp->rv32__DOT__result = (vlTOPp->rv32__DOT__num1 
                                         - ((IData)(1U) 
                                            + (~ vlTOPp->rv32__DOT__num2)));
        } else {
            if ((3U == (IData)(vlTOPp->rv32__DOT__aluc))) {
                vlTOPp->rv32__DOT__result = (0xfffffffeU 
                                             & (vlTOPp->rv32__DOT__num1 
                                                + vlTOPp->rv32__DOT__num2));
            } else {
                vlTOPp->__Vdpiimwrap_rv32__DOT__control_unit_inst__DOT__ebreak_TOP(2U, 0xdeafbeafU, 1U);
            }
        }
    }
    vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3[0U] 
        = (IData)((0x100000000ULL | (QData)((IData)(vlTOPp->rv32__DOT__result))));
    vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3[1U] 
        = ((0xfffffffeU & ((IData)((QData)((IData)(
                                                   ((IData)(4U) 
                                                    + vlTOPp->rv32__DOT__pc)))) 
                           << 1U)) | (IData)(((0x100000000ULL 
                                               | (QData)((IData)(vlTOPp->rv32__DOT__result))) 
                                              >> 0x20U)));
    vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3[2U] 
        = ((1U & ((IData)((QData)((IData)(((IData)(4U) 
                                           + vlTOPp->rv32__DOT__pc)))) 
                  >> 0x1fU)) | (0xfffffffeU & ((IData)(
                                                       ((QData)((IData)(
                                                                        ((IData)(4U) 
                                                                         + vlTOPp->rv32__DOT__pc))) 
                                                        >> 0x20U)) 
                                               << 1U)));
    vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3[0U] 
        = (IData)((0x100000000ULL | (QData)((IData)(vlTOPp->rv32__DOT__result))));
    vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3[1U] 
        = ((0xfffffffeU & ((IData)((QData)((IData)(vlTOPp->rv32__DOT__pc))) 
                           << 1U)) | (IData)(((0x100000000ULL 
                                               | (QData)((IData)(vlTOPp->rv32__DOT__result))) 
                                              >> 0x20U)));
    vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3[2U] 
        = ((1U & ((IData)((QData)((IData)(vlTOPp->rv32__DOT__pc))) 
                  >> 0x1fU)) | (0xfffffffeU & ((IData)(
                                                       ((QData)((IData)(vlTOPp->rv32__DOT__pc)) 
                                                        >> 0x20U)) 
                                               << 1U)));
    vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[0U] = 0U;
    vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[1U] 
        = (3U | (0xfffffffcU & (vlTOPp->rv32__DOT__mem_rdata 
                                << 2U)));
    vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[2U] 
        = (8U | ((0xfffffff0U & (vlTOPp->rv32__DOT__result 
                                 << 4U)) | (3U & (vlTOPp->rv32__DOT__mem_rdata 
                                                  >> 0x1eU))));
    vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[3U] 
        = (0x10U | ((0xffffffc0U & ((IData)((QData)((IData)(
                                                            ((IData)(4U) 
                                                             + vlTOPp->rv32__DOT__pc)))) 
                                    << 6U)) | (0xfU 
                                               & (vlTOPp->rv32__DOT__result 
                                                  >> 0x1cU))));
    vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[4U] 
        = ((0x3fU & ((IData)((QData)((IData)(((IData)(4U) 
                                              + vlTOPp->rv32__DOT__pc)))) 
                     >> 0x1aU)) | (0xffffffc0U & ((IData)(
                                                          ((QData)((IData)(
                                                                           ((IData)(4U) 
                                                                            + vlTOPp->rv32__DOT__pc))) 
                                                           >> 0x20U)) 
                                                  << 6U)));
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[0U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3[1U])) 
                              << 0x20U) | (QData)((IData)(
                                                          vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3[0U]))));
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[1U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3[2U])) 
                              << 0x1fU) | ((QData)((IData)(
                                                           vlTOPp->rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3[1U])) 
                                           >> 1U)));
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list[0U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3[1U])) 
                              << 0x20U) | (QData)((IData)(
                                                          vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3[0U]))));
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list[1U] 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3[2U])) 
                              << 0x1fU) | ((QData)((IData)(
                                                           vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber3[1U])) 
                                           >> 1U)));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[0U] 
        = (0x3ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[1U])) 
                              << 0x20U) | (QData)((IData)(
                                                          vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[0U]))));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[1U] 
        = (0x3ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[3U])) 
                              << 0x3eU) | (((QData)((IData)(
                                                            vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[2U])) 
                                            << 0x1eU) 
                                           | ((QData)((IData)(
                                                              vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[1U])) 
                                              >> 2U))));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[2U] 
        = (0x3ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[4U])) 
                              << 0x3cU) | (((QData)((IData)(
                                                            vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[3U])) 
                                            << 0x1cU) 
                                           | ((QData)((IData)(
                                                              vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[2U])) 
                                              >> 4U))));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list[3U] 
        = (0x3ffffffffULL & (((QData)((IData)(vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[4U])) 
                              << 0x1aU) | ((QData)((IData)(
                                                           vlTOPp->rv32__DOT____Vcellinp__i4____pinNumber3[3U])) 
                                           >> 6U)));
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[0U] 
        = (IData)(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list
                  [0U]);
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[1U] 
        = (IData)(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list
                  [1U]);
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[0U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list
                         [0U] >> 0x20U)));
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[1U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list
                         [1U] >> 0x20U)));
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list[0U] 
        = (IData)(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list
                  [0U]);
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list[1U] 
        = (IData)(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list
                  [1U]);
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list[0U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list
                         [0U] >> 0x20U)));
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list[1U] 
        = (1U & (IData)((vlTOPp->rv32__DOT__i5__DOT__i0__DOT__pair_list
                         [1U] >> 0x20U)));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[0U] 
        = (IData)(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                  [0U]);
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[1U] 
        = (IData)(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                  [1U]);
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[2U] 
        = (IData)(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                  [2U]);
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list[3U] 
        = (IData)(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                  [3U]);
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[0U] 
        = (3U & (IData)((vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                         [0U] >> 0x20U)));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[1U] 
        = (3U & (IData)((vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                         [1U] >> 0x20U)));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[2U] 
        = (3U & (IData)((vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                         [2U] >> 0x20U)));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list[3U] 
        = (3U & (IData)((vlTOPp->rv32__DOT__i4__DOT__i0__DOT__pair_list
                         [3U] >> 0x20U)));
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__hit 
        = ((IData)(vlTOPp->rv32__DOT__m3) == vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list
           [0U]);
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__hit 
        = ((IData)(vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__hit) 
           | ((IData)(vlTOPp->rv32__DOT__m3) == vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list
              [1U]));
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out 
        = ((- (IData)(((IData)(vlTOPp->rv32__DOT__m3) 
                       == vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list
                       [0U]))) & vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list
           [0U]);
    vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out 
        = (vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out 
           | ((- (IData)(((IData)(vlTOPp->rv32__DOT__m3) 
                          == vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list
                          [1U]))) & vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list
              [1U]));
    vlTOPp->rv32__DOT__PC_inst__DOT__pc_temp = vlTOPp->rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out;
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber2) 
                                                == 
                                                vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list
                                                [0U]);
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__i5__DOT__i0__DOT__hit) 
                                                | ((IData)(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber2) 
                                                   == 
                                                   vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list
                                                   [1U]));
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__lut_out = 
        ((- (IData)(((IData)(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber2) 
                     == vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list
                     [0U]))) & vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list
         [0U]);
    vlTOPp->rv32__DOT__i5__DOT__i0__DOT__lut_out = 
        (vlTOPp->rv32__DOT__i5__DOT__i0__DOT__lut_out 
         | ((- (IData)(((IData)(vlTOPp->rv32__DOT____Vcellinp__i5____pinNumber2) 
                        == vlTOPp->rv32__DOT__i5__DOT__i0__DOT__key_list
                        [1U]))) & vlTOPp->rv32__DOT__i5__DOT__i0__DOT__data_list
            [1U]));
    vlTOPp->rv32__DOT__raddr = vlTOPp->rv32__DOT__i5__DOT__i0__DOT__lut_out;
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__m4) 
                                                == 
                                                vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                                                [0U]);
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit) 
                                                | ((IData)(vlTOPp->rv32__DOT__m4) 
                                                   == 
                                                   vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                                                   [1U]));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit) 
                                                | ((IData)(vlTOPp->rv32__DOT__m4) 
                                                   == 
                                                   vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                                                   [2U]));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit = ((IData)(vlTOPp->rv32__DOT__i4__DOT__i0__DOT__hit) 
                                                | ((IData)(vlTOPp->rv32__DOT__m4) 
                                                   == 
                                                   vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                                                   [3U]));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out = 
        ((- (IData)(((IData)(vlTOPp->rv32__DOT__m4) 
                     == vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                     [0U]))) & vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list
         [0U]);
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out = 
        (vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out 
         | ((- (IData)(((IData)(vlTOPp->rv32__DOT__m4) 
                        == vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                        [1U]))) & vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list
            [1U]));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out = 
        (vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out 
         | ((- (IData)(((IData)(vlTOPp->rv32__DOT__m4) 
                        == vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                        [2U]))) & vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list
            [2U]));
    vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out = 
        (vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out 
         | ((- (IData)(((IData)(vlTOPp->rv32__DOT__m4) 
                        == vlTOPp->rv32__DOT__i4__DOT__i0__DOT__key_list
                        [3U]))) & vlTOPp->rv32__DOT__i4__DOT__i0__DOT__data_list
            [3U]));
    vlTOPp->rv32__DOT__rin = vlTOPp->rv32__DOT__i4__DOT__i0__DOT__lut_out;
    vlTOPp->__Vdpiimwrap_rv32__DOT__mem_inst__DOT__pmem_read_TOP(vlTOPp->rv32__DOT__raddr, vlTOPp->__Vfunc_rv32__DOT__mem_inst__DOT__pmem_read__0__Vfuncout);
    vlTOPp->rv32__DOT__mem_rdata = vlTOPp->__Vfunc_rv32__DOT__mem_inst__DOT__pmem_read__0__Vfuncout;
    if (vlTOPp->rv32__DOT____Vcellinp__mem_inst__wen_m) {
        vlTOPp->__Vdpiimwrap_rv32__DOT__mem_inst__DOT__pmem_write_TOP(vlTOPp->rv32__DOT__result, vlTOPp->rv32__DOT__src2, (IData)(vlTOPp->rv32__DOT__wmask));
    }
}

void Vrv32::_eval(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_eval\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
        vlTOPp->__Vm_traceActivity[1U] = 1U;
    }
    vlTOPp->_settle__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity[2U] = 1U;
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
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
    __req |= ((vlTOPp->rv32__DOT__mem_rdata ^ vlTOPp->__Vchglast__TOP__rv32__DOT__mem_rdata));
    VL_DEBUG_IF( if(__req && ((vlTOPp->rv32__DOT__mem_rdata ^ vlTOPp->__Vchglast__TOP__rv32__DOT__mem_rdata))) VL_DBG_MSGF("        CHANGE: /home/uae/ysyx/ysyx-workbench/npc/vsrc/rv32.v:130: rv32.mem_rdata\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__rv32__DOT__mem_rdata = vlTOPp->rv32__DOT__mem_rdata;
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
