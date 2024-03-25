#include "../include/common.h"
#include "../include/utils.h"
#include "../include/debug.h"
#include "../include/macro.h"
#include "Vrv32.h"


/********extern functions or variables********/
extern void single_cycle(void); 
extern NPCState npc_state;
extern Vrv32 *top;

#ifdef CONFIG_FTRACE 
extern void RET_Log(uint32_t pc, uint32_t npc);
extern void J_Log(uint32_t pc, uint32_t npc);
#define OPCODE(inst)  ((inst) & 0x7f)
#endif

#ifdef CONFIG_IRINGBUF 
extern void append_iringbuf(char *s);
extern void display_iringbuf(void);
#endif
/*********************************************/


#define MAX_INST_TO_PRINT 20
static uint64_t g_nr_guest_inst = 0;
static bool g_print_step = false;
IFDEF(CONFIG_ITRACE, char logbuf[128]);

static struct {
  word_t pc;
  word_t npc;
  word_t inst;
  word_t ninst;
} PCSet = {0, 0, 0, 0};


static void statistic() {
    Log("total guest instructions = %lu", g_nr_guest_inst);
}

static void execute_once() 
{
    //观察波形图可以发现，执行reset后第一条指令已经执行了1/3，即取指、译码部分已经完成，此时的pc为当前pc，执行剩下的2/3后pc为dnpc
    PCSet.pc = top->pc;  PCSet.inst = top->inst;
    single_cycle();  single_cycle();  single_cycle();      // take 3 cycles to excute one instruction
    PCSet.npc = top->pc;  PCSet.ninst = top->inst;

#ifdef CONFIG_ITRACE
    char *p = logbuf;
    p += snprintf(p, sizeof(logbuf), "0x%08x: 0x%08x ", PCSet.pc, top->inst);
    *p = '\0';
    // // Log("%s",logbuf);
    // // Log("%ld, 0x%08x %d", logbuf + sizeof(logbuf) - p, PCSet.pc, 4);
    // char temp[64] = {0};
    // uint32_t inst = 0x00000513;
    // void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
    // // disassemble(p, logbuf + sizeof(logbuf) - p, PCSet.pc, (uint8_t *)&top->inst, 4);
    // disassemble(temp, sizeof(temp), 0x8000000c, (uint8_t *)&inst, 4);
#endif

#ifdef CONFIG_FTRACE
  if(PCSet.inst == 0x00008067)  //ret
    RET_Log(PCSet.pc, PCSet.npc);
  else if((OPCODE(PCSet.inst)==0b1100111) || (OPCODE(PCSet.inst)== 0b1101111))  //jalr or jal
    J_Log(PCSet.pc, PCSet.npc);
#endif

#ifdef CONFIG_IRINGBUF 
    append_iringbuf(logbuf);
#endif
}

static void trace_and_difftest() 
{
    // itrace
    #ifdef CONFIG_ITRACE
        log_write("%s\n", logbuf);
    #endif
    if(g_print_step) 
        IFDEF(CONFIG_ITRACE, puts(logbuf)); 

    // difftest
//   IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));

}

static void execute(uint64_t n) 
{
    for (;n > 0; n --) 
    {    
        execute_once();
        g_nr_guest_inst ++;
        trace_and_difftest();
        if (npc_state.state != NPC_RUNNING) 
            break;
    }
}


void cpu_exec(uint64_t n) 
{
    g_print_step = (n < MAX_INST_TO_PRINT);
    switch (npc_state.state) 
    {
        case NPC_END: case NPC_ABORT:
            printf("Program execution has ended. To restart the program, exit NPC and run again.\n");
            return;
        default: npc_state.state = NPC_RUNNING;
    }   

    execute(n);

    switch (npc_state.state) 
    {
        case NPC_RUNNING: npc_state.state = NPC_STOP; break;

        case NPC_END: case NPC_ABORT:
#ifdef CONFIG_IRINGBUF 
            display_iringbuf();
#endif
            Log("NPC: %s at pc =  0x%08x",
                (npc_state.state == NPC_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
                (npc_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
                    ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
                npc_state.halt_pc);
        case NPC_QUIT: statistic();
    }
}