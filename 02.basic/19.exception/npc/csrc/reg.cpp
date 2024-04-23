#include "../include/common.h"
#include "../include/debug.h"
#include "Vrv32.h"


/********extern functions or variables********/
extern Vrv32 *top;
/*********************************************/


#define top_gprs      top->rv32__DOT__register_file_inst__DOT__regs
#define top_mstatus   top->rv32__DOT__csr_regs_inst__DOT__mstatus
#define top_mtvec     top->rv32__DOT__csr_regs_inst__DOT__mtvec
#define top_mepc      top->rv32__DOT__csr_regs_inst__DOT__mepc
#define top_mcause    top->rv32__DOT__csr_regs_inst__DOT__mcause

static const char *regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void regs_display() 
{
    _Log(ANSI_FG_RED "RegName  Hex_Value       Dec_Value\n" ANSI_NONE);
    _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\n", "pc", 
         top->rv32__DOT__pc, top->rv32__DOT__pc);
    for(int i = 0; i < 32; i++)
    {
        _Log(ANSI_FG_YELLOW "$%s\t " ANSI_NONE, regs[i]);
        _Log("0x%08x\t %010u\n", top_gprs[i], top_gprs[i]);
    }
}

void single_reg_display(char *reg_name) 
{
    int i;
    //pc
    _Log(ANSI_FG_RED "RegName  Hex_Value       U-Dec_Value       Dec_Value\n\33[0m");
    if(strcmp(reg_name, "pc") == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u %010d\n", "pc", 
             top->rv32__DOT__pc, top->rv32__DOT__pc, top->rv32__DOT__pc);
        return;
    }

    //reg $0
    if(strcmp(reg_name, regs[0]) == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", 
             "$0", top_gprs[1], top_gprs[1], top_gprs[1]);
        return;
    }      

    //other gprs
    for(i = 1; i < 32; i++)
        if(strcmp(reg_name, regs[i]) == 0)
        {
            _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", 
                 regs[i], top_gprs[i], top_gprs[i], top_gprs[i]);
            return;
        }
    
    // mstatus
    if(strcmp(reg_name, "mstatus") == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mstatus", 
            top_mstatus, top_mstatus, top_mstatus);
        return;
    }
    // mtvec;
    if(strcmp(reg_name, "mtvec") == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s  "     ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mtvec", 
            top_mtvec, top_mtvec, top_mtvec);
        return;
    }
    // mepc;
    if(strcmp(reg_name, "mepc") == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s   "      ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mepc", 
            top_mepc, top_mepc, top_mepc);
        return;
    }
    // mcause;
    if(strcmp(reg_name, "mcause") == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s " ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "mcause", 
            top_mcause, top_mcause, top_mcause);
        return;
    }

    Warn("No register %s.", reg_name);
}

word_t reg_str2val(const char *s, bool *success) 
{
    int i;
    //pc
    if(strcmp(s, "pc") == 0)
        return top->rv32__DOT__pc; 
        
    //reg $0
    if(strcmp(s, regs[0]) == 0)
        return top_gprs[0];
        
    //others
    for(i = 1; i < 32; i++)
        if(strcmp(s, regs[i]) == 0)
        return top_gprs[i];

    //no reg name matched
    *success = false;
    return 0;
}