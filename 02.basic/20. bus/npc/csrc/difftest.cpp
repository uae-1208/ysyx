#include "../include/difftest.h"
#include <dlfcn.h>
#include "Vrv32.h"


/********extern functions or variables********/
extern Vrv32 *top;
extern NPCState npc_state;
extern uint8_t* guest_to_host(paddr_t paddr);
/*********************************************/

#ifdef CONFIG_DIFFTEST

#define top_gprs top->rv32__DOT__register_file_inst__DOT__regs

CPU_state cpu;
static bool skip_flag = false; // the flag to skip the ref 

void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;

void difftest_skip_ref() {
  skip_flag = true;
}

const char *ref_regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};


static void update_cpu_state(CPU_state *cpu)
{
    cpu->pc = top->rv32__DOT__bru_inst__DOT__npc_reg;
    for(int i = 0; i < 32; i++)
        cpu->gpr[i] = top_gprs[i];
    
    // 0x300 -> 0.mstatus;
    // 0x305 -> 1.mtvec;
    // 0x341 -> 2.mepc;
    // 0x342 -> 3.mcause;
    cpu->csr[0] = top->rv32__DOT__csr_ctrl_inst__DOT__mstatus;
    cpu->csr[1] = top->rv32__DOT__csr_ctrl_inst__DOT__mtvec;
    cpu->csr[2] = top->rv32__DOT__csr_ctrl_inst__DOT__mepc;
    cpu->csr[3] = top->rv32__DOT__csr_ctrl_inst__DOT__mcause;
}


void init_difftest(char *ref_so_file, long img_size, int port) 
{
    update_cpu_state(&cpu);

    assert(ref_so_file != NULL);

    void *handle;
    handle = dlopen(ref_so_file, RTLD_LAZY);
    assert(handle);

    ref_difftest_memcpy = (void (*)(uint32_t, void*, size_t, bool))dlsym(handle, "difftest_memcpy");
    assert(ref_difftest_memcpy);

    ref_difftest_regcpy = (void (*)(void*, bool))dlsym(handle, "difftest_regcpy");
    assert(ref_difftest_regcpy);

    ref_difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
    assert(ref_difftest_exec);

    // ref_difftest_raise_intr = dlsym(handle, "difftest_raise_intr");
    // assert(ref_difftest_raise_intr);

    void (*ref_difftest_init)(int) = (void (*)(int))dlsym(handle, "difftest_init");
    assert(ref_difftest_init);

    Log("The result of every instruction will be compared with %s. "
        "This will help you a lot for debugging, but also significantly reduce the performance. ", ref_so_file);

    ref_difftest_init(port);
    ref_difftest_memcpy(RESET_VECTOR, guest_to_host(RESET_VECTOR), img_size, DIFFTEST_TO_REF);
    ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}


bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) 
{
    bool success = true;

    //check pc
    if(ref_r->pc != pc)
    {
        _Log(ANSI_FG_YELLOW "[difftest]" ANSI_NONE   ANSI_FG_RED "pc" 
             ANSI_NONE "  dut:0x%08x   ref:0x%08x\n", pc, ref_r->pc);
        success = false;
    }

    //check general purpose registers
    for(int i = 0; i < 32; i++)
        if(top_gprs[i] != ref_r->gpr[i])
        {
            _Log(ANSI_FG_YELLOW "[difftest]" ANSI_NONE   ANSI_FG_RED "%s" 
                 ANSI_NONE "  dut:0x%08x   ref:0x%08x\n", ref_regs[i], top_gprs[i], ref_r->gpr[i]);
            success = false;
        }
        
    return success;
}

static void checkregs(CPU_state *ref, vaddr_t pc, vaddr_t npc) 
{
    if (!isa_difftest_checkregs(ref, npc)) 
    {
        npc_state.state = NPC_ABORT;
        npc_state.halt_pc = pc;
        Log("Differential test %s at pc = 0x%08x." , (ANSI_FMT("fails", ANSI_FG_RED)), npc_state.halt_pc);
    }
}

void difftest_step(vaddr_t pc, vaddr_t npc) 
{
    CPU_state ref_r;
    update_cpu_state(&cpu);

    if(skip_flag == true)
    {
        // to skip the checking of an instruction, just copy the reg state to reference design
        ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
        skip_flag = false;
        return;
    }

    ref_difftest_exec(1);
    ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);

    checkregs(&ref_r, pc, npc);
}


#else
void init_difftest(char *ref_so_file, long img_size, int port) { }
#endif