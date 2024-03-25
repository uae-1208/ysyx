#include "../include/common.h"
#include "../include/debug.h"
#include "../include/paddr.h"
#include "../include/macro.h"
#include "../include/utils.h"
#include <getopt.h>


/********extern functions or variables********/
extern void     init_log(const char *log_file);
extern void     init_sdb();
extern void     init_mem(void);
extern uint8_t* guest_to_host(paddr_t paddr);

#ifdef CONFIG_FTRACE 
extern void load_elf(void);
#endif
/*********************************************/


static char *log_file = NULL;
static char *img_file = NULL;
NPCState npc_state = { .state = NPC_STOP };


#ifdef CONFIG_FTRACE 
char *elf_file = NULL;
#endif

int is_exit_status_bad() 
{
    int good = (npc_state.state == NPC_END && npc_state.halt_ret == 0) || (npc_state.state == NPC_QUIT);
    return !good;
}

static void welcome()
{
    Log("ITrace:   %s", MUXDEF(CONFIG_ITRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    Log("MTrace:   %s", MUXDEF(CONFIG_MTRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    Log("FTrace:   %s", MUXDEF(CONFIG_FTRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    Log("IRingBuf: %s", MUXDEF(CONFIG_IRINGBUF, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    IFDEF(CONFIG_TRACE, Log("If trace is enabled, a log file will be generated "
        "to record the trace. This may lead to a large log file. "
        "If it is not necessary, you can disable it in menuconfig"));
    Log("Build time: %s, %s", __TIME__, __DATE__);
    printf("Welcome to %s-NPC!\n", ANSI_FMT("riscv32e", ANSI_FG_YELLOW ANSI_BG_RED));
    printf("For help, type \"help\"\n");
}


static long load_img() 
{
  if (img_file == NULL) {
    Log("No image is given. Use the default build-in image.");
    return 4096; // built-in image size
  }

  FILE *fp = fopen(img_file, "rb");
  Assert(fp, "Can not open '%s'", img_file);

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);

  Log("The image is %s, size = %ld", img_file, size);

  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
  assert(ret == 1);

  fclose(fp);
  return size;
}



static int parse_args(int argc, char *argv[]) 
{
    const struct option table[] = {
        {"batch"    , no_argument      , NULL, 'b'},
        {"log"      , required_argument, NULL, 'l'},
        {"help"     , no_argument      , NULL, 'h'},
        {"elf"      , required_argument, NULL, 'e'},
        {0          , 0                , NULL,  0 },
    };
    int o;
    while ( (o = getopt_long(argc, argv, "-bhl:e:", table, NULL)) != -1) {
        switch (o) {
            case 'l': log_file = optarg; break;
            case 'e': elf_file = optarg; break; 
            case 1  : img_file = optarg; return 0;
            default :
            printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
            printf("\t-b,--batch              run with batch mode\n");
            printf("\t-l,--log=FILE           output log to FILE\n");
            printf("\t-e,--elf=FILE           input elf FILE to support MTRACE\n");
            printf("\n");
            exit(0);
        }
    }
    return 0;
}

void init_monitor(int argc, char *argv[]) {
    /* Perform some global initialization. */

    /* Parse arguments. */
    parse_args(argc, argv);

    /* Open the log file. */
    init_log(log_file);

#ifdef CONFIG_FTRACE 
    /* Load the ELF file of the image */
    load_elf();
#endif

    /* Initialize memory. */
    init_mem();

    /* Load the image to memory. This will overwrite the built-in image. */
    long img_size = load_img();

    /* Initialize the simple debugger. */
    init_sdb();

    /* Display welcome message. */
    welcome();
}

