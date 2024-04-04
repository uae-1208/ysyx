#include "../include/common.h"
#include "../include/debug.h"
#include "../include/utils.h"
#include <readline/readline.h>
#include <readline/history.h>


/********extern functions or variables********/
extern void     cpu_exec(uint64_t n); 
extern void     regs_display(); 
extern void     init_regex();
extern void     single_reg_display(char *reg_name); 
extern word_t   reg_str2val(const char *s, bool *success); 
extern uint8_t* guest_to_host(paddr_t paddr);
extern word_t   host_read(void *addr, int len);
extern word_t   expr(char *e, bool *success);

/*********************************************/


static int is_batch_mode = false;


static int cmd_c(char *args) {
    cpu_exec(-1);
    return 0;
}
static int cmd_q(char *args) {return -1;}
static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args);


static struct {
    const char *name;
    const char *description;
    int (*handler) (char *);
} cmd_table [] = {
    { "help", "Display information about all supported commands", cmd_help },
    { "c", "Continue the execution of the program", cmd_c },
    { "q", "Exit NEMU", cmd_q },
    { "si", "Excute N instruction(s)", cmd_si },
    { "info", "Display information about registers", cmd_info },
    { "x", "Display memory content of N word(s) in HEX", cmd_x },
    { "p", "Get the value of the expression", cmd_p },
};



#define NR_CMD ARRLEN(cmd_table)


static int cmd_si(char *args) 
{
    /* extract the first argument */
    char *buff = strtok(NULL, " ");
    //The number of instruction to excute.
    int inst_num = 0;

    if (buff == NULL) 
        /* no argument given */
        inst_num = 1;
    else 
        //extract the number by converting  char* into int
        sscanf(buff, "%d", &inst_num);
    
    _Log(ANSI_FG_BLUE "%d instruction(s) excuted.\n" ANSI_NONE, inst_num);
    cpu_exec(inst_num);
    return 0;
}


static int cmd_info(char *args) 
{
    /* extract the first argument */
    char *buff = strtok(NULL, " ");

    if (buff == NULL) 
    {
        /* no argument given */
        Warn("Input 'r' for registers!");
    }
    else 
    {
        if(strcmp(buff, "r") == 0)
        {
            //register
            _Log(ANSI_FG_BLUE "Display register information.\n" ANSI_NONE);
            buff = strtok(NULL, " ");
            if(buff == NULL)
                regs_display();
            else
                single_reg_display(buff);
        }
        else
            Warn("Unknown arguments '%s'. Input 'r' for registers", buff);
    }
    return 0;
}


static int cmd_x(char *args)
{
    /* extract the first argument */
    char *buf = NULL;
    int word_num = 0;     //The number of words to display.
    vaddr_t mem_addr = 0;
    bool success = true;

    /* no argument given */
    if(args == NULL)
    {
        Warn("No argument inputed!");
        return 0;
    }

    buf = strtok(NULL, " ");
    //the number argument
    sscanf(buf, "%d", &word_num);

    //the addrdess argument
    buf = strtok(NULL, "");
    if (buf == NULL) 
    {
        /* no argument given */
        Warn("No memory address inputed!");
        return 0;
    }
    else 
    {
        mem_addr = expr(buf, &success);
        assert(success == true);
    }

    _Log(ANSI_FG_BLUE "Display memory content of %d words:\n" ANSI_NONE, word_num);
    _Log(ANSI_FG_RED " Address       value\n" ANSI_NONE);   
    for(int i = 0; i < word_num; i++, mem_addr+=4)
    {
        _Log(ANSI_FG_YELLOW "[0x%08x]:" ANSI_NONE, mem_addr);
        _Log("  0x%08x\n",host_read(guest_to_host(mem_addr), 4));
    }
    return 0;
}

static int cmd_p(char *args) 
    {
    bool success = true;
    uint32_t result;

    if (args == NULL) 
        /* no argument given */
        Warn("No expression inputed!");
    else 
    {
        result = expr(args, &success);
        _Log(ANSI_FG_BLUE "%s = %u\n" ANSI_NONE, args, result);
    }
    assert(success == true);  
    return 0;
}

static int cmd_help(char *args) {
    /* extract the first argument */
    char *arg = strtok(NULL, " ");
    int i;

    if (arg == NULL) {
        /* no argument given */
        for (i = 0; i < NR_CMD; i ++) 
            printf("  %s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
    else 
    {
        for (i = 0; i < NR_CMD; i ++) {
            if (strcmp(arg, cmd_table[i].name) == 0)
            {
                printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
                return 0;
            }
    }
        printf("Unknown command '%s'\n", arg);
    }
    return 0;
}


/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() 
{
    static char *line_read = NULL;
    if (line_read) 
    {
        free(line_read);
        line_read = NULL;
    }

    line_read = readline("(ysyx)--" ANSI_FG_GREEN "npc@uae: " ANSI_NONE);
    if (line_read && *line_read) 
        add_history(line_read);

    return line_read;
}

void sdb_set_batch_mode(void) 
{
  is_batch_mode = true;
}


void sdb_mainloop() 
{
    if(is_batch_mode) 
    {
        cmd_c(NULL);
        return;
    }

    for (char *str; (str = rl_gets()) != NULL; ) 
    {
        char *str_end = str + strlen(str);

        /* extract the first token as the command */
        char *cmd = strtok(str, " ");
        if (cmd == NULL) { continue; }

        /* treat the remaining string as the arguments,
        * which may need further parsing
        */
        char *args = cmd + strlen(cmd) + 1;
        if (args >= str_end) 
            args = NULL;

    int i;
    for (i = 0; i < NR_CMD; i ++) 
    {
        if (strcmp(cmd, cmd_table[i].name) == 0) 
        {
            if (cmd_table[i].handler(args) < 0) 
                return;
            break;
        }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}



void init_sdb() 
{
  /* Compile the regular expressions. */
  init_regex();
}