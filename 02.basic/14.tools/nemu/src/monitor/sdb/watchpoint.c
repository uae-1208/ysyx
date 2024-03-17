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

#include "sdb.h"
#include <memory/paddr.h>
#include <memory/host.h>


#define NR_WP 32
#define EXPR_SIZE 50

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char expr[EXPR_SIZE];
  uint32_t old_val, new_val;
} WP;

// static WP wp_pool[NR_WP] = {};
//uae doesn't want to use the wp_pool, but the dynamic distribution
static WP *head, *tail;
static int wp_amount; //the amount of existing wp
static int wp_no;     //the biggest wp number

void init_wp_pool() {
  // int i;
  // for (i = 0; i < NR_WP; i ++) {
  //   wp_pool[i].NO = i;
  //   wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  // }
  // 
  head = NULL;
  tail = NULL;
  wp_amount = 0;
  wp_no = 0;
  // free_ = wp_pool;
}


/* TODO: Implement the functionality of watchpoint */
//create a watchpoint
void new_wp(char *expr)
{
  if(head == NULL)
  {
    head = (WP*)malloc(sizeof(WP));
    tail = head;
  }
  else
  {
    tail->next = (WP*)malloc(sizeof(WP));
    tail = tail->next;
  }
  tail->next = NULL;
  strcpy(tail->expr, expr);
  wp_no++;
  wp_amount++;
  tail->NO = wp_no;
  tail->old_val = rand();
  tail->new_val = rand();
}


//delete a watchpoint
int free_wp(int NO)
{
  WP *temp = head;
  WP *t = NULL;
  //no wp existed
  if(wp_amount == 0)
    return 1;

  //the first wp is what we want
  if(head->NO == NO)
  {
    head = head->next;
    free(temp);
    if(wp_amount == 1)  //only one wp existed
      tail = NULL;
    wp_amount--;
    return 0;       //delete the wp labelled with NO successfully
  }

  //the first wp is not what we want
  while((temp->next != NULL) && (temp->next->NO != NO))
    temp = temp->next;
  
  //no wp labell with NO
  if(temp->next == NULL)
    return 2;

  assert(temp->next->NO == NO);
  if(tail == temp->next)  //if deleting the tail wp
    tail = temp;
  t = temp->next;
  temp->next = t->next;
  wp_amount--;
  free(t);
  return 0;         //delete the wp labelled with NO successfully
}


//display all existing watchpoints
void wp_display(void)
{
  WP *temp = head;
  //"\33[1;31m" means red，"\n\33[0m" means returning to default
  printf("\33[1;31mNum    Type          Disp Enb Address\n\33[0m");
  
  while(temp != NULL)
  {
    printf("%02d     ", temp->NO);
    printf("hw watchpoint ");
    printf("keep ");
    printf("y   ");
    printf("%s\n", temp->expr);
    
    temp = temp->next;
  }
}


//scan all existing watchpoints to check if them change
bool scan_all_wps(void)
{
  WP *temp = head;
  bool change_happens = false;
  bool success = true;
  vaddr_t mem_addr = 0;

  while(temp != NULL)
  {
    mem_addr = expr(temp->expr, &success);
    assert(success == true);
    temp->old_val = temp->new_val;
    temp->new_val = host_read(guest_to_host(mem_addr), 4);
    if(temp->old_val != temp->new_val)
    {
      change_happens = true;
      printf("\33[1;31mHardware watchpoint %d:\33[0m %s\n", temp->NO, temp->expr);
      printf("\33[1;31mValue old\33[0m = %u\n", temp->old_val);
      printf("\33[1;31mValue new\33[0m = %u\n", temp->new_val);
    }

    temp = temp->next;
  }

  return change_happens;
}

