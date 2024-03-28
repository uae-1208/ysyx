#include "../include/common.h"
#include "../include/debug.h"


/********extern functions or variables********/
#ifdef CONFIG_FTRACE 
extern char *elf_file;
#endif
/*********************************************/



/******************************ftrace******************************/
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
static uint32_t check_func_interval(uint32_t pc)
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

void load_elf(void) 
{
    if (elf_file == NULL){
        Log("No ELF file is given.");
            return;
    }

    ftrace_log = fopen("./log/ftrace-log.txt", "w");
    assert(ftrace_log != NULL);

    fp = fopen(elf_file, "rb");
    Assert(fp, "Can not open '%s'", elf_file);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    _Log(ANSI_FG_BLUE "The ELF file is %s, size = %ld.\n" ANSI_NONE, elf_file, size);
    fprintf(ftrace_log, "The ELF file is %s, size = %ld.\n", elf_file, size); 

    // ELF Header
    fseek(fp, 0, SEEK_SET); 
    int ret = fread(&ELF_header, sizeof(Elf32_Ehdr), 1, fp);  
    assert(ret == 1); 
    _Log(ANSI_FG_BLUE "Amount of section headers: %d.\n" ANSI_NONE, ELF_header.e_shnum);
    _Log(ANSI_FG_BLUE "Start of section headers: 0x%x.\n" ANSI_NONE, ELF_header.e_shoff);
    fprintf(ftrace_log, "Amount of section headers: %d.\n", ELF_header.e_shnum); 
    fprintf(ftrace_log, "Start of section headers: 0x%x.\n", ELF_header.e_shoff); 
    
    // symbol table
    fseek(fp, ELF_header.e_shoff + (ELF_header.e_shnum - 3) * sizeof(Elf32_Shdr), SEEK_SET); //symtab section in Section Headers
    ret = fread(&symtab, sizeof(Elf32_Shdr), 1, fp);
    assert(ret == 1);
    _Log(ANSI_FG_BLUE "Start of symtab: 0x%x.\n" ANSI_NONE, symtab.sh_offset);
    fprintf(ftrace_log, "Start of symtab: 0x%x\n", symtab.sh_offset); 
    sym_amount = symtab.sh_size / sizeof(Elf32_Sym);
    _Log(ANSI_FG_BLUE "The amount of symbol(s): %d\n" ANSI_NONE, sym_amount);
    fprintf(ftrace_log, "The amount of symbol(s): %d\n", sym_amount); 

    //string table
    ret = fread(&strtab, sizeof(Elf32_Shdr), 1, fp);         //strtab section in Section Headers
    assert(ret == 1);
    _Log(ANSI_FG_BLUE "Start of strtab: 0x%x\n" ANSI_NONE, strtab.sh_offset);     //name strings of symbols
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
    _Log(ANSI_FG_BLUE "Infomation about FUNC symbol(s):\n" ANSI_NONE);
    fprintf(ftrace_log, "Infomation about FUNC symbol(s):\n"); 
    for(int i = 0; i < func_amount; i++)
    {
        Get_sym_name(sym_fun_group[i].name_index, sym_fun_group[i].name);
        printf(ANSI_FG_BLUE " %-10s" ANSI_NONE "   addr: 0x%08x   size: %d\n", 
               sym_fun_group[i].name, sym_fun_group[i].value, sym_fun_group[i].size);
        fprintf(ftrace_log, " %-10s   addr: 0x%08x   size: %d\n", 
                sym_fun_group[i].name, sym_fun_group[i].value, sym_fun_group[i].size); 
    }

    fprintf(ftrace_log, "\n\n");
    fflush(ftrace_log); 
    fclose(fp);
}
#endif
/******************************************************************/


/*****************************iringbuf*****************************/
#ifdef CONFIG_IRINGBUF 

struct IRINGBUF
{
    char inst_buf[MAX_iringbuf_size][64];
    int head, tail;
};

static struct IRINGBUF iringbuf = {
    .inst_buf = {""},
    .head = 0,
    .tail = 0
};

void append_iringbuf(char *s)
{
    // if(iringbuf.inst_buf[iringbuf.head] != NULL)
    if(strcmp(iringbuf.inst_buf[iringbuf.head], ""))    //the iringbuf is not currently empty
    {
        iringbuf.tail = (iringbuf.tail + 1) % MAX_iringbuf_size;  
        if(iringbuf.head == iringbuf.tail)                //the iringbuf is currently full
        iringbuf.head = (iringbuf.head + 1) % MAX_iringbuf_size;
    }

    strcpy(iringbuf.inst_buf[iringbuf.tail], s);
}

void display_iringbuf(void)
{
    int i = iringbuf.head;
    if(iringbuf.inst_buf[i] == NULL)
        return;

    _Log(ANSI_FG_BLUE "Display inst iringbuf:\n" ANSI_NONE);
    while(i != iringbuf.tail)
    {
        printf(ANSI_FG_YELLOW "[iringbuf] " ANSI_NONE "      %s\n", iringbuf.inst_buf[i]);
        log_write("[iringbuf]       %s\n", iringbuf.inst_buf[i]); 
        i = (i + 1) % MAX_iringbuf_size;
    }
    printf(ANSI_FG_YELLOW "[iringbuf] " ANSI_NONE ANSI_FG_RED "---->" ANSI_NONE " %s\n", 
           iringbuf.inst_buf[iringbuf.tail]);
    log_write("[iringbuf] ----> %s\n", iringbuf.inst_buf[iringbuf.tail]); 
}
#endif
/******************************************************************/