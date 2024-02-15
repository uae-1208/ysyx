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
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
/**********Appended by uae**********/
#include <memory/paddr.h>
#include <memory/host.h>
/***********************************/


static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);
/*Handlers appended by uae*/
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args);
/**************************/


static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },

  /* TODO: Add more commands */
  { "si", "Excute N instruction(s)", cmd_si },
  { "info", "Display information about registers or watch points", cmd_info },
  { "x", "Display memory content of N word(s) in HEX", cmd_x },
  { "p", "Get the value of the expression", cmd_p },

};

#define NR_CMD ARRLEN(cmd_table)



/*Handlers appended by uae*/

static int cmd_si(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  //The number of instruction to excute.
  int inst_num = 0;

  if (arg == NULL) 
    /* no argument given */
    inst_num = 1;
  else 
    //extract the number by converting  char* into int
    sscanf(arg, "%d", &inst_num);
  
  Log("%d instruction(s) excuted.", inst_num);
  cpu_exec(inst_num);
  return 0;
}


static int cmd_info(char *args) 
{
  /* extract the first argument */
  char *arg = strtok(NULL, " ");

  if (arg == NULL) 
  {
    /* no argument given */
    printf("Input 'r' for registers or 'w' for watch points.\n");
  }
  else 
  {
    if('r' == *arg)
    {
      //register
      Log("Display register information.");
      isa_reg_display();
    }
    else if('w' == *arg)
    {
      //watch point
      printf("Something not appended yet. Be patient!\n");
    }
    else
    {
      printf("Unknown arguments '%s'. ", arg);
      printf("Input 'r' for registers or 'w' for watch points.\n");
    }
  }
  
  return 0;
}


static int cmd_x(char *args)
{
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  //The number of words to display.
  int word_num = 0;
  vaddr_t mem_addr = 0;

  //the number argument
  //extract the number by converting  char* into int
  sscanf(arg, "%d", &word_num);
  

  //the addrdess argument
  arg = strtok(NULL, " ");
  if (arg == NULL) 
  {
    /* no argument given */
    printf("No memory address inputed.\n");
    return 0;
  }
  else 
    //extract the number by converting  char* into int
    sscanf(arg, "%x", &mem_addr);   //consider the input as hex


  Log("Display memory content of %d words.", word_num);
  printf(" Address       value\n");
  for(int i = 0; i < word_num; i++, mem_addr+=4)
    printf("[0x%08x]:  0x%08x\n", mem_addr, host_read(guest_to_host(mem_addr), 4));
  
  return 0;
}


static int cmd_p(char *args) 
{
  //uae
  bool a = 1;

  if (args == NULL) 
    /* no argument given */
    printf("No expression inputed.\n");
  else 
    expr(args, &a);

  return 0;
}
/**************************/



static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
