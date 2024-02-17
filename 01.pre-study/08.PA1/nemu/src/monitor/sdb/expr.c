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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <string.h>
#include <stdbool.h>

enum
{
  TK_NOTYPE = 256,
  TK_EQ,
  /* TODO: Add more token types */
  TK_INT,

};

static struct rule
{
  const char *regex;
  int token_type;
} rules[] = {

    /* TODO: Add more rules.
     * Pay attention to the precedence level of different rules.
     */

    {" +", TK_NOTYPE}, // spaces
    {"\\+", '+'},      // plus
    {"==", TK_EQ},     // equal
    {"[0-9]", TK_INT}, // dec_int
    {"\\-", '-'},      // substract
    {"\\*", '*'},      // multiply
    {"\\/", '/'},      // divide
    {"\\(", '('},      // left parenthesis
    {"\\)", ')'},      // right parenthesis
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++)
  {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0)
    {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token
{
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;    //the amount of the recognized token 

static bool make_token(char *e)
{
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0')
  {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++)
    {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
      {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        switch (rules[i].token_type)
        {
          case TK_NOTYPE: break;      //ignore the space
          default:                    //record the recognized token 
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            //make sure the string end with '\0'
            tokens[nr_token].str[substr_len] = '\0';   
            nr_token++;
        }

        break;
      }
    }

    if (i == NR_REGEX)
    {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  return true;
}

static bool check_parentheses(int start, int end)
{
  //The first token is "(", otherwise returns false
  int num_Lparentheses = 1;   //The amount of "(" by now
  if((strcmp(tokens[start].str, "(") != 0) || (strcmp(tokens[end].str, ")") != 0))
    return false;

  for(int i = start + 1; i <= end; i++)
  {
    if((strcmp(tokens[i].str, "(") == 0))   //encounter a "("
      num_Lparentheses++;
    else if((strcmp(tokens[i].str, ")") == 0)) //when encountering a ")", eliminate a "("
    {
      if(num_Lparentheses > 1)    //the first "(" is not eliminated yet
        num_Lparentheses--;
      else if((num_Lparentheses == 1) && (i == end))  //the first "(" and the last ")"
        return true;
      else 
        return false;
    }
  }
  return false;
}

#define Is_op(c)  (((c) == '+') || ((c) == '-') || ((c) == '*') || ((c) == '/'))
//check whether the "prime" is primer than the "token" ['+'= '-' > '*' = '/']
static bool check_precedence(char prime, char token)
{
  assert((prime == '+') || (prime == '-') || (prime == '*') || (prime == '/'));
  assert((token == '+') || (token == '-') || (token == '*') || (token == '/'));

  if((token == '+') || (token == '-'))
    return false;
  else if((token == '*') || (token == '/'))
  {
    if((prime == '+') || (prime == '-'))
      return true;
    else
      return false;
  }
  return false;
}

//get the position of the prime operator
static int get_prime(int start, int end)
{
  int num_Lparentheses = 0;   //The amount of "(" by now
  int p_op_position = start;
  char p_op_type = '*';


  for(int i = start; i <= end; i++)
  {
    if((strcmp(tokens[i].str, "(") == 0))   //encounter a "("
      num_Lparentheses++;
    else if((strcmp(tokens[i].str, ")") == 0))  //when encountering a ")", eliminate a "("
      num_Lparentheses--;
    else   //the token is either a number or a operator
    {
      if(num_Lparentheses < 0)  //wrong expression
        return -1;
      else if(num_Lparentheses == 0) //the token if out of one parentheses
      {
        //the token is an operator and is primer
        if(Is_op(tokens[i].str[0]) && !check_precedence(p_op_type, tokens[i].str[0]))
        {
          p_op_position = i;   
          p_op_type = tokens[i].str[0];
        }
      }
    }
  }

  if(num_Lparentheses < 0)  //wrong expression
    return -1;
  if(p_op_position == start) //no operator found
    return -1;

  return p_op_position;
}

static uint32_t eval(int p, int q)
{
  if (p > q) {
    /* Bad expression */
    assert(0);
  }
  else if (p == q) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    return (tokens[p].str[0] - '0');
  }
  else if(check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1);
  }
  else {
    /* We should do more things here. */
    int op = get_prime(p, q);         assert(op != -1);
    uint32_t val1 = eval(p, op - 1);
    uint32_t val2 = eval(op + 1, q);

    switch (tokens[op].str[0]) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      default: assert(0);
    }
  }
}

word_t expr(char *e, bool *success)
{
  if (!make_token(e))
  {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  printf("%s = %u\n", e, eval(0, nr_token-1));


  /*1. testing make_token()*/
  // {
  //   for(int i = 0; i < nr_token; i++)
  //     printf("%s",tokens[i].str);
  //   printf("\n");
  // }
  
  /*2. testing check_parentheses()*/
  // {
  //   for(int i = 0; i < nr_token; i++)
  //     printf("%s",tokens[i].str);
  //   printf("      %s!\n", check_parentheses(0, nr_token-1) ? "true" : "false");
  // }

  /*3. testing get_prime()*/
  // {
  //   for(int i = 0; i < nr_token; i++)
  //     printf("%s",tokens[i].str);
  //   printf("\n");
  //   for(int i = 0; i < nr_token; i++)
  //     printf("[%d]%s  ",i, tokens[i].str);
  //   printf("\nprime:%d\n",get_prime(0, nr_token-1)); 
  // }
  
  /*4. testing eval()*/
  // {
  //   uint32_t result, eval_result;
  //   int ret;
  //   char buff[40];
  //   char* p;
  //   FILE *fp = fopen("/home/uae/ysyx/ysyx-workbench/nemu/tools/gen-expr/uae", "r");
  //   assert(fp != NULL);
  //   for(int i = 0; i < 988; i++)
  //   {
  //     ret = fscanf(fp, "%u ", &result);   assert(ret != 0);//fscanf读取字符串时无法读取空格
  //     p = fgets(buff, 40, fp);   assert(p != NULL);  //fgets遇到\n时结束读取，但会读取进\n
  //     buff[strlen(buff) - 1] = '\0';     //删除\n
  //     assert(make_token(buff) == 1);
  //     eval_result = eval(0, nr_token-1);
  //     printf("%s = %u",buff ,eval_result);
  //     printf("     result=%u\n", result);
  //     assert(result == eval_result);
  //   }
  // }

  return 0;
}
