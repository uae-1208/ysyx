#include "../include/common.h"
#include "../include/debug.h"
#include "Vrv32.h"


/********extern functions or variables********/
extern Vrv32 *top;
/*********************************************/


#define gpr top->rv32__DOT__register_file_inst__DOT__regs

static const char *regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void regs_display() 
{
    _Log(ANSI_FG_RED "RegName  Hex_Value       Dec_Value\n" ANSI_NONE);
    _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\n", "pc", top->pc, top->pc);
    for(int i = 0; i < 32; i++)
    {
        _Log(ANSI_FG_YELLOW "$%s\t " ANSI_NONE, regs[i]);
        _Log("0x%08x\t %010u\n", gpr[i], gpr[i]);
    }
}

void single_reg_display(char *reg_name) 
{
    int i;
    //pc
    _Log(ANSI_FG_RED "RegName  Hex_Value       U-Dec_Value       Dec_Value\n\33[0m");
    if(strcmp(reg_name, "pc") == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u %010d\n", "pc", top->pc, top->pc, top->pc);
        return;
    }

    //reg $0
    if(strcmp(reg_name, regs[0]) == 0)
    {
        _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", "$0", gpr[1], gpr[1], gpr[1]);
        return;
    }      

    //others
    for(i = 1; i < 32; i++)
        if(strcmp(reg_name, regs[i]) == 0)
        {
            _Log(ANSI_FG_YELLOW "$%s\t" ANSI_NONE " 0x%08x\t %010u\t   %010d\n", regs[i], gpr[i], gpr[i], gpr[i]);
            return;
        }

    Warn("No register %s.", reg_name);
}

word_t reg_str2val(const char *s, bool *success) 
{
    int i;
    //pc
    if(strcmp(s, "pc") == 0)
        return top->pc; 
        
    //reg $0
    if(strcmp(s, regs[0]) == 0)
        return gpr[0];
        
    //others
    for(i = 1; i < 32; i++)
        if(strcmp(s, regs[i]) == 0)
        return gpr[i];

    //no reg name matched
    *success = false;
    return 0;
}