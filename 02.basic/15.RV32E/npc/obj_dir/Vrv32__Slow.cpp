// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrv32.h for the primary calling header

#include "Vrv32.h"
#include "Vrv32__Syms.h"

#include "verilated_dpi.h"

//==========

Vrv32::Vrv32(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModule{_vcname__}
 {
    Vrv32__Syms* __restrict vlSymsp = __VlSymsp = new Vrv32__Syms(_vcontextp__, this, name());
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vrv32::__Vconfigure(Vrv32__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    vlSymsp->_vm_contextp__->timeunit(-12);
    vlSymsp->_vm_contextp__->timeprecision(-12);
}

Vrv32::~Vrv32() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = nullptr);
}

void Vrv32::_eval_initial(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_eval_initial\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vrv32::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::final\n"); );
    // Variables
    Vrv32__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vrv32::_eval_settle(Vrv32__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_eval_settle\n"); );
    Vrv32* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity[2U] = 1U;
    vlTOPp->__Vm_traceActivity[1U] = 1U;
    vlTOPp->__Vm_traceActivity[0U] = 1U;
}

void Vrv32::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    inst = VL_RAND_RESET_I(32);
    pc = VL_RAND_RESET_I(32);
    rv32__DOT__type4 = VL_RAND_RESET_I(3);
    rv32__DOT__wen = VL_RAND_RESET_I(1);
    rv32__DOT__m1 = VL_RAND_RESET_I(1);
    rv32__DOT__m2 = VL_RAND_RESET_I(1);
    rv32__DOT__m3 = VL_RAND_RESET_I(1);
    rv32__DOT__m4 = VL_RAND_RESET_I(1);
    rv32__DOT__aluc = VL_RAND_RESET_I(2);
    rv32__DOT__result = VL_RAND_RESET_I(32);
    rv32__DOT__rin = VL_RAND_RESET_I(32);
    rv32__DOT__src1 = VL_RAND_RESET_I(32);
    rv32__DOT__num1 = VL_RAND_RESET_I(32);
    rv32__DOT__num2 = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(66, rv32__DOT____Vcellinp__i1____pinNumber3);
    VL_RAND_RESET_W(66, rv32__DOT____Vcellinp__i2____pinNumber3);
    VL_RAND_RESET_W(66, rv32__DOT____Vcellinp__i4____pinNumber3);
    rv32__DOT__clk_count_inst__DOT__clk_cnt = VL_RAND_RESET_I(2);
    rv32__DOT__PC_inst__DOT__pc_temp = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(66, rv32__DOT__PC_inst__DOT____Vcellinp__i3____pinNumber3);
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__pair_list[__Vi0] = VL_RAND_RESET_Q(33);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__key_list[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__data_list[__Vi0] = VL_RAND_RESET_I(32);
    }
    rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__lut_out = VL_RAND_RESET_I(32);
    rv32__DOT__PC_inst__DOT__i3__DOT__i0__DOT__hit = VL_RAND_RESET_I(1);
    rv32__DOT__register_file_inst__DOT__i = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<32; ++__Vi0) {
        rv32__DOT__register_file_inst__DOT__regs[__Vi0] = VL_RAND_RESET_I(32);
    }
    rv32__DOT__imm_extend_inst__DOT__imm_12 = VL_RAND_RESET_I(12);
    rv32__DOT__imm_extend_inst__DOT__imm_20 = VL_RAND_RESET_I(20);
    rv32__DOT__imm_extend_inst__DOT__imm_12_to_32 = VL_RAND_RESET_I(32);
    rv32__DOT__imm_extend_inst__DOT__imm_20_to_32 = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i1__DOT__i0__DOT__pair_list[__Vi0] = VL_RAND_RESET_Q(33);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i1__DOT__i0__DOT__key_list[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i1__DOT__i0__DOT__data_list[__Vi0] = VL_RAND_RESET_I(32);
    }
    rv32__DOT__i1__DOT__i0__DOT__lut_out = VL_RAND_RESET_I(32);
    rv32__DOT__i1__DOT__i0__DOT__hit = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i2__DOT__i0__DOT__pair_list[__Vi0] = VL_RAND_RESET_Q(33);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i2__DOT__i0__DOT__key_list[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i2__DOT__i0__DOT__data_list[__Vi0] = VL_RAND_RESET_I(32);
    }
    rv32__DOT__i2__DOT__i0__DOT__lut_out = VL_RAND_RESET_I(32);
    rv32__DOT__i2__DOT__i0__DOT__hit = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i4__DOT__i0__DOT__pair_list[__Vi0] = VL_RAND_RESET_Q(33);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i4__DOT__i0__DOT__key_list[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        rv32__DOT__i4__DOT__i0__DOT__data_list[__Vi0] = VL_RAND_RESET_I(32);
    }
    rv32__DOT__i4__DOT__i0__DOT__lut_out = VL_RAND_RESET_I(32);
    rv32__DOT__i4__DOT__i0__DOT__hit = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<3; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}
