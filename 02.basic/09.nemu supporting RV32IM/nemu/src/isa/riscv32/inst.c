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

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write

enum {
  TYPE_R, TYPE_I, TYPE_S, TYPE_B, TYPE_U, TYPE_J,
  TYPE_N, // none
};

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immB() do { int imm12_11 = (SEXT(BITS(i, 31, 31), 1) << 1) | BITS(i, 7, 7);  \
                    int imm12_5  = (imm12_11 << 6) | BITS(i, 30, 25);                \
                           *imm  = (imm12_5 << 4) | BITS(i, 11, 8); } while(0)
#define immJ() do { int imm20_12 = (SEXT(BITS(i, 31, 31), 1) << 8) | BITS(i, 19, 12); \
                    int imm20_11 = (imm20_12 << 1) | BITS(i, 20, 20);                 \
                           *imm  = (imm20_11 << 10) | BITS(i, 30, 21); } while(0)

static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst.val;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_R: src1R(); src2R();         break;
    case TYPE_I: src1R();          immI(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_B: src1R(); src2R(); immB(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_J:                   immJ(); break;
  }
}

static int decode_exec(Decode *s) {
  int rd = 0;
  word_t src1 = 0, src2 = 0, imm = 0;
  s->dnpc = s->snpc;

#define INSTPAT_INST(s) ((s)->isa.inst.val)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}

  INSTPAT_START();
  INSTPAT("0000000 ????? ????? 000 ????? 01100 11", add    , R, R(rd) = src1 + src2);
  INSTPAT("0100000 ????? ????? 000 ????? 01100 11", sub    , R, R(rd) = src1 - src2);
  INSTPAT("0000000 ????? ????? 001 ????? 01100 11", sll    , R, R(rd) = src1 << src2);
  INSTPAT("0000000 ????? ????? 011 ????? 01100 11", sltu   , R, R(rd) = ((uint32_t)src1 < (uint32_t)src2));
  INSTPAT("0000000 ????? ????? 100 ????? 01100 11", xor    , R, R(rd) = src1 ^ src2);
  INSTPAT("0100000 ????? ????? 101 ????? 01100 11", sra    , R, R(rd) = src1 >> src2);
  INSTPAT("0000000 ????? ????? 110 ????? 01100 11", or     , R, R(rd) = src1 | src2);
  INSTPAT("0000000 ????? ????? 111 ????? 01100 11", and    , R, R(rd) = src1 & src2);
  INSTPAT("??????? ????? ????? 000 ????? 00100 11", addi   , I, R(rd) = src1 + imm);
  INSTPAT("??????? ????? ????? 011 ????? 00100 11", sltiu  , I, R(rd) = ((uint32_t)src1 < (uint32_t)imm));
  //12位立即数为：0100000_xxxxx，取低五位
  INSTPAT("0100000 ????? ????? 101 ????? 00100 11", srai   , I, imm = (imm & 31); R(rd) = src1 >> imm);
  INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd) = src1 ^ imm);
  INSTPAT("??????? ????? ????? 111 ????? 00100 11", andi   , I, R(rd) = src1 & imm);
  //JALR指令会把12位立即数和源寄存器相加，并把相加结果末位清零，作为新的跳转地址。同时和JAL指令一样，也会把紧随其后的那条指令地址，存入目标寄存器中。
  INSTPAT("??????? ????? ????? 000 ????? 11001 11", jalr   , I, s->dnpc = (src1 + imm) & ~1; R(rd) = s->pc + 4);  
  INSTPAT("??????? ????? ????? 010 ????? 00000 11", lw     , I, R(rd) = Mr(src1 + imm, 4));
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = Mr(src1 + imm, 1));
  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, Mw(src1 + imm, 1, src2));
  INSTPAT("??????? ????? ????? 001 ????? 01000 11", sh     , S, Mw(src1 + imm, 2, src2));
  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, Mw(src1 + imm, 4, src2));
  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B, if(src1 == src2) {s->dnpc = s->pc + (imm << 1);});
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B, if(src1 != src2) {s->dnpc = s->pc + (imm << 1);});
  //adds the offset to the address of the AUIPC instruction
  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = s->pc + imm);   
  //jal, x1, offset>>1
  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J, s->dnpc = s->pc + (imm << 1); R(rd) = s->pc + 4); 


  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10))); // R(10) is $a0
  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc));
  INSTPAT_END();

  //pseudo  instructions
  // INSTPAT("??????? ????? ????? 000 ????? 00100 11", li     , I, R(rd) = src1 + imm);    //li r, imm == addi reg, x0, imm
  // INSTPAT("??????? ????? ????? 000 ????? 11001 11", ret    , I, s->pc = (src1 + imm) & ~1, R(rd) = s->pc + 4);  //== jalr x0, x1, 0
  // INSTPAT("??????? ????? ????? 000 ????? 00100 11", mv     , I, R(rd) = src1 + imm);   // mv reg1, reg2 == addi reg1, reg2, 0
  // INSTPAT("??????? ????? ????? 011 ????? 00100 11", seqz   , I, R(rd) = ((uint32_t)src1 < (uint32_t)imm));   //Set if = zero ： seqz rd, rs == sltiu rd, rs, 1 
  // INSTPAT("??????? ????? ????? 000 ????? 11000 11", beqz   , B, if(src1 == src2) {s->dnpc = s->pc + (imm << 1);});   //beqz rs, offset ==  beq rs, x0, offset
  // INSTPAT("??????? ????? ????? 001 ????? 11000 11", bnez   , B, if(src1 != src2) {s->dnpc = s->pc + (imm << 1);});   //bnez rs, offset ==  bne rs, x0, offset
  // INSTPAT("??????? ????? ????? ??? ????? 11011 11", j      , J, s->dnpc = s->pc + (imm << 1), R(rd) = s->pc + 4); //jal, offset == jal, x0, offset>>1

  R(0) = 0; // reset $zero to 0

  return 0;
}

int isa_exec_once(Decode *s) {
  s->isa.inst.val = inst_fetch(&s->snpc, 4);
  return decode_exec(s);
}


