// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    
    // DPI IMPORTS
    // DPI import at /home/uae/ysyx/ysyx-workbench/npc/vsrc/mem.v:21:34
    extern void ebreak(int station, int inst, char unit);
    // DPI import at /home/uae/ysyx/ysyx-workbench/npc/vsrc/mem.v:19:34
    extern int pmem_read(int raddr);
    // DPI import at /home/uae/ysyx/ysyx-workbench/npc/vsrc/mem.v:20:34
    extern void pmem_write(int waddr, int wdata, char wmask);
    
#ifdef __cplusplus
}
#endif
