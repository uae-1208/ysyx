// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VRV32_H_
#define VERILATED_VRV32_H_  // guard

#include "verilated_heavy.h"

//==========

class Vrv32__Syms;
class Vrv32_VerilatedVcd;


//----------

VL_MODULE(Vrv32) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN(inst,31,0);
    VL_OUT(pc,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*1:0*/ rv32__DOT__PC_inst__DOT__clk_div4;
    CData/*0:0*/ rv32__DOT__i1__DOT__i0__DOT__hit;
    SData/*11:0*/ rv32__DOT__imm_extend_inst__DOT__imm_12;
    IData/*31:0*/ rv32__DOT__result;
    IData/*31:0*/ rv32__DOT__num2;
    IData/*31:0*/ rv32__DOT__register_file_inst__DOT__i;
    IData/*31:0*/ rv32__DOT__i1__DOT__i0__DOT__lut_out;
    IData/*31:0*/ rv32__DOT__register_file_inst__DOT__regs[32];
    QData/*32:0*/ rv32__DOT__i1__DOT__i0__DOT__pair_list[2];
    CData/*0:0*/ rv32__DOT__i1__DOT__i0__DOT__key_list[2];
    IData/*31:0*/ rv32__DOT__i1__DOT__i0__DOT__data_list[2];
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst;
    WData/*65:0*/ rv32__DOT____Vcellinp__i1____pinNumber3[3];
    CData/*0:0*/ __Vm_traceActivity[3];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vrv32__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vrv32);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vrv32(VerilatedContext* contextp, const char* name = "TOP");
    Vrv32(const char* name = "TOP")
      : Vrv32(nullptr, name) {}
    /// Destroy the model; called (often implicitly) by application code
    ~Vrv32();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Return current simulation context for this model.
    /// Used to get to e.g. simulation time via contextp()->time()
    VerilatedContext* contextp();
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
    static void _eval_initial_loop(Vrv32__Syms* __restrict vlSymsp);
    void __Vconfigure(Vrv32__Syms* symsp, bool first);
  private:
    static QData _change_request(Vrv32__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vrv32__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__2(Vrv32__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vrv32__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vrv32__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vrv32__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(Vrv32__Syms* __restrict vlSymsp);
  private:
    static void traceChgSub0(void* userp, VerilatedVcd* tracep);
    static void traceChgTop0(void* userp, VerilatedVcd* tracep);
    static void traceCleanup(void* userp, VerilatedVcd* /*unused*/);
    static void traceFullSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceFullTop0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitTop(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    void traceRegister(VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
