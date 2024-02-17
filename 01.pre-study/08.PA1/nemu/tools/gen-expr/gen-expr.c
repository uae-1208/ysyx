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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

int choose(int num)
{
  return rand() % num;
}

static char* gen_num(void) 
{
  int num = choose(9) + 1;  //1-9
  char* str = (char*)malloc(11 * sizeof(char));
  str[0] = '0' + num;
  str[1] = '\0';
  return str;
}

// static char* gen_space(void) 
// {
//   int num = choose(5) + 2;  //1-5(except one space byte)
//   char* str = (char*)malloc(num * sizeof(char));
// 
//   for(int i = 0; i < num - 1; i++)
//     strcat(str, " ");
//   str[num - 1] = '\0';
// 
//   return str;
// }

static char* gen(char c) 
{
  char* str = (char*)malloc(2 * sizeof(char));
  str[0] = c;
  str[1] = '\0';
  return str;
}

static char* gen_rand_op(void) 
{
  char* str = (char*)malloc(2 * sizeof(char));

  switch (choose(4)) 
  {
    case 0: str[0] = '+'; break;
    case 1: str[0] = '-'; break;
    case 2: str[0] = '*'; break;
    case 3: str[0] = '/'; break;
    default: assert(0); break;
  }
  str[1] = '\0';

  return str;
}

#define token_size 32  //according to the KISS principle, 从简单的情况的开始（tokens数组长度为32）
static char* random_expr(void) 
{
  char* str = (char*)malloc(2 * token_size * sizeof(char));
  char * temp;
  str[0] = '\0';

  switch (choose(3)) 
  {
    case 0: return gen_num(); 
    case 1: temp = gen('(');        strcat(str, temp);  free(temp);
            temp = random_expr();   strcat(str, temp);  free(temp);
            temp = gen(')');        strcat(str, temp);  free(temp);
            break;
    case 2: temp = random_expr();   strcat(str, temp);  free(temp); 
            temp = gen_rand_op();   strcat(str, temp);  free(temp);
            temp = random_expr();   strcat(str, temp);  free(temp);
            break;
    default: assert(0); break;
  }

  //If the recursion result is too long (longer then token_size), then replace the result with "( 1 + 2)"
  if(strlen(str) > token_size)  
    strcpy(str, "( 1 + 2)");

  return str;
}

void gen_rand_expr() 
{
  char* str = random_expr();
  memcpy(buf, str, strlen(str)+1);
  free(str);
}

int main(int argc, char *argv[]) {
  
  int seed = time(NULL);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    //If division_by_zero occurs, then the compilation fails and ret = -1
    int ret = system("gcc -O2 -Wall -Werror /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
