/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <memory/paddr.h>

// #define CONFIG_IRINGBUF 1
// #define CONFIG_MTRACE   1
// #define CONFIG_FTRACE   1

void init_rand();
void init_log(const char *log_file);
void init_mem();
void init_difftest(char *ref_so_file, long img_size, int port);
void init_device();
void init_sdb();
void init_disasm(const char *triple);

static void welcome() {
    Log("ITrace:   %s", MUXDEF(CONFIG_ITRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    Log("MTrace:   %s", MUXDEF(CONFIG_MTRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    Log("FTrace:   %s", MUXDEF(CONFIG_FTRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    // Log("IRingBuf: %s", MUXDEF(CONFIG_IRINGBUF, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
    Log("DiffTest: %s", MUXDEF(CONFIG_DIFFTEST, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
  IFDEF(CONFIG_TRACE, Log("If trace is enabled, a log file will be generated "
        "to record the trace. This may lead to a large log file. "
        "If it is not necessary, you can disable it in menuconfig"));
  Log("Build time: %s, %s", __TIME__, __DATE__);
  printf("Welcome to %s-NEMU!\n", ANSI_FMT(str(__GUEST_ISA__), ANSI_FG_YELLOW ANSI_BG_RED));
  printf("For help, type \"help\"\n");
  //Log("Exercise: Please remove me in the source code and compile NEMU again.");
  //assert(0);
}

#ifndef CONFIG_TARGET_AM
#include <getopt.h>

void sdb_set_batch_mode();

static char *log_file = NULL;
static char *diff_so_file = NULL;
static char *img_file = NULL;
static int difftest_port = 1234;
static char *elf_file = NULL;



/********************************ftrace********************************/
#ifdef CONFIG_FTRACE 

#include <elf.h>
typedef struct {
    uint32_t   name_index;            //Elf32_Sym.st_name
    char       name[20];              //Elf32_Sym's name
    Elf32_Addr value;                 //Elf32_Sym.st_value
    uint32_t   size;                  //Elf32_Sym.st_size
}Func_Sym;

#define Is_FUNC(info)  ((ELF32_ST_TYPE(info)) == STT_FUNC)
#define MAX_func_size 32               //the max amount of FUNC symbols
static int func_amount = 0;            //FUNC symbol amount
static Func_Sym sym_fun_group[MAX_func_size] = {0};

static Elf32_Ehdr ELF_header = {0};     //ELF Header
static Elf32_Shdr symtab = {0};         //symbol table section
static Elf32_Shdr strtab = {0};         //string table section (containing name strings of symbols)
static Elf32_Sym sym_temp = {0};        //symbol temp

FILE *fp;                               //ELF FILE
static int sym_amount = 0;              //symbok amount
static char sym_name_buff[20] = {0};    //symbol name string temp


FILE *ftrace_log ;    // the log recording ftrace infomation
uint32_t loop = 0;    // the depth of calls
uint32_t check_func_interval(uint32_t pc)
{
  int i;
  for(i = 0; i < func_amount; i++)
  {
    uint32_t addr_s = sym_fun_group[i].value;
    uint32_t addr_e = sym_fun_group[i].value + sym_fun_group[i].size;
    if(addr_s <= pc && pc < addr_e)
      break;
  }
  assert(i < func_amount);
  return i;
}


// if the inst is ret, log the call
void RET_Log(uint32_t pc, uint32_t npc)
{
  // Log("s->pc:%x, s->dnpc:%x", pc, npc);
  loop--;
  //get the FUNC symbol index in sym_fun_group
  uint32_t index = check_func_interval(npc);   
  fprintf(ftrace_log, "[ftrace] 0x%08x: ", pc); 
  //print the certain amount of '  '
  for(int i=0; i<loop; i++)                           
    fprintf(ftrace_log, "  "); 
  fprintf(ftrace_log, "ret [%s]\n", sym_fun_group[index].name); 
  fflush(ftrace_log); 
}



// if the inst is jal or jalr(other than ret), log the call
void J_Log(uint32_t pc, uint32_t npc)
{
  // Log("s->pc:%x, s->dnpc:%x", pc, npc);
  //get the FUNC symbol index in sym_fun_group
  uint32_t index = check_func_interval(npc);
  fprintf(ftrace_log, "[ftrace] 0x%08x: ", pc); 
  //print the certain amount of '  '
  for(int i=0; i<loop; i++)
    fprintf(ftrace_log, "  "); 
  fprintf(ftrace_log, "call[%s@0x%08x]\n", sym_fun_group[index].name, sym_fun_group[index].value); 
  fflush(ftrace_log); 
  loop++;
}


//look up names of symbols in the strtab
static void Get_sym_name(uint32_t name_index, char *name)
{
  int i = 0;
  fseek(fp, (strtab.sh_offset + name_index), SEEK_SET);      //strtab.sh_offset is the start of string table (those strings are the names of symbols)
  int ret = fread((sym_name_buff + i), 1, 1, fp);  assert(ret == 1);
  i++;
  while(1)
  {
    ret = fread((sym_name_buff + i), 1, 1, fp);   assert(ret == 1);
    if(sym_name_buff[i++] == 0)   // == '.' in strtab
      break;
  }
  sym_name_buff[i-1] = '\0';     
  strcpy(name, sym_name_buff);
}

static void load_elf(void) {
  if (elf_file == NULL){
    Log("No ELF file is given.");
    return;
  }

  ftrace_log = fopen("./build/ftrace-log.txt", "w");
  assert(ftrace_log != NULL);

  fp = fopen(elf_file, "rb");
  Assert(fp, "Can not open '%s'", elf_file);

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  Log("The ELF file is %s, size = %ld.", elf_file, size);
  fprintf(ftrace_log, "The ELF file is %s, size = %ld.\n", elf_file, size); 

  // ELF Header
  fseek(fp, 0, SEEK_SET); 
  int ret = fread(&ELF_header, sizeof(Elf32_Ehdr), 1, fp);  
  assert(ret == 1); 
  Log("Amount of section headers: %d.", ELF_header.e_shnum);
  Log("Start of section headers: 0x%x.", ELF_header.e_shoff);
  fprintf(ftrace_log, "Amount of section headers: %d.\n", ELF_header.e_shnum); 
  fprintf(ftrace_log, "Start of section headers: 0x%x.\n", ELF_header.e_shoff); 
  
  // symbol table
  fseek(fp, ELF_header.e_shoff + (ELF_header.e_shnum - 3) * sizeof(Elf32_Shdr), SEEK_SET); //symtab section in Section Headers
  ret = fread(&symtab, sizeof(Elf32_Shdr), 1, fp);
  assert(ret == 1);
  Log("Start of symtab: 0x%x", symtab.sh_offset);
  fprintf(ftrace_log, "Start of symtab: 0x%x\n", symtab.sh_offset); 
  sym_amount = symtab.sh_size / sizeof(Elf32_Sym);
  Log("The amount of symbol(s): %d", sym_amount);
  fprintf(ftrace_log, "The amount of symbol(s): %d\n", sym_amount); 

  //string table
  ret = fread(&strtab, sizeof(Elf32_Shdr), 1, fp);         //strtab section in Section Headers
  assert(ret == 1);
  Log("Start of strtab: 0x%x", strtab.sh_offset);     //name strings of symbols
  fprintf(ftrace_log, "Start of strtab: 0x%x\n", strtab.sh_offset); 

  // read every symbol to find FUNC symbol
  fseek(fp, symtab.sh_offset, SEEK_SET);                //Start of symbol table
  for(int i = 0; i < sym_amount; i++)
  {
    ret = fread(&sym_temp, sizeof(Elf32_Sym), 1, fp);
    assert(ret == 1);
    if(Is_FUNC(sym_temp.st_info))
    {
      sym_fun_group[func_amount].name_index = sym_temp.st_name;
      sym_fun_group[func_amount].size = sym_temp.st_size;
      sym_fun_group[func_amount].value = sym_temp.st_value;
      func_amount++;
    }
    assert(func_amount <= MAX_func_size);   // avoid sym_fun_group overflow
  }


  //get the name for every func symbol
  Log("Infomation about FUNC symbol(s):");
  fprintf(ftrace_log, "Infomation about FUNC symbol(s):\n"); 
  for(int i = 0; i < func_amount; i++)
  {
    Get_sym_name(sym_fun_group[i].name_index, sym_fun_group[i].name);
    printf(" \33[1;32m%-10s\33[0m   addr: 0x%08x   size: %d\n", sym_fun_group[i].name, sym_fun_group[i].value, sym_fun_group[i].size);
    fprintf(ftrace_log, " %-10s   addr: 0x%08x   size: %d\n", sym_fun_group[i].name, sym_fun_group[i].value, sym_fun_group[i].size); 
  }

  fprintf(ftrace_log, "\n\n");
  fflush(ftrace_log); 
  fclose(fp);
}
#endif
/**********************************************************************/



static long load_img() {
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


static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"batch"    , no_argument      , NULL, 'b'},
    {"log"      , required_argument, NULL, 'l'},
    {"diff"     , required_argument, NULL, 'd'},
    {"port"     , required_argument, NULL, 'p'},
    {"help"     , no_argument      , NULL, 'h'},
    {"elf"      , required_argument, NULL, 'e'},
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-bhl:d:p:e:", table, NULL)) != -1) {
    switch (o) {
      case 'b': sdb_set_batch_mode(); break;
      case 'p': sscanf(optarg, "%d", &difftest_port); break;
      case 'l': log_file = optarg; break;
      case 'd': diff_so_file = optarg; break;
      case 'e': elf_file = optarg; break;  //uae
      case 1: img_file = optarg; return 0;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\t-b,--batch              run with batch mode\n");
        printf("\t-l,--log=FILE           output log to FILE\n");
        printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
        printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
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

  /* Set random seed. */
  init_rand();

  /* Open the log file. */
  init_log(log_file);

  /* Initialize memory. */
  init_mem();

  /* Initialize devices. */
  IFDEF(CONFIG_DEVICE, init_device());

  /* Perform ISA dependent initialization. */
  init_isa();

  /* Load the image to memory. This will overwrite the built-in image. */
  long img_size = load_img();

#ifdef CONFIG_FTRACE 
/* Load the ELF file of the image */
  load_elf();
#endif

  /* Initialize differential testing. */
  init_difftest(diff_so_file, img_size, difftest_port);

  /* Initialize the simple debugger. */
  init_sdb();

#ifndef CONFIG_ISA_loongarch32r
  IFDEF(CONFIG_ITRACE, init_disasm(
    MUXDEF(CONFIG_ISA_x86,     "i686",
    MUXDEF(CONFIG_ISA_mips32,  "mipsel",
    MUXDEF(CONFIG_ISA_riscv,
      MUXDEF(CONFIG_RV64,      "riscv64",
                               "riscv32"),
                               "bad"))) "-pc-linux-gnu"
  ));
#endif

  /* Display welcome message. */
  welcome();
}
#else // CONFIG_TARGET_AM
static long load_img() {
  extern char bin_start, bin_end;
  size_t size = &bin_end - &bin_start;
  Log("img size = %ld", size);
  memcpy(guest_to_host(RESET_VECTOR), &bin_start, size);
  return size;
}

void am_init_monitor() {
  init_rand();
  init_mem();
  init_isa();
  load_img();
  IFDEF(CONFIG_DEVICE, init_device());
  welcome();
}
#endif
