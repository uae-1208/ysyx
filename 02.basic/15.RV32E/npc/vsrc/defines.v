// reset
`define RST_VAL 1'b1


// I type instruction
`define INST_TYPE_I 7'b001_0011
`define INST_ADDI 3'b000


// U type instruction
`define INST_TYPE_AUIPC 7'b001_0111


// E type instruction
`define INST_TYPE_E   7'b111_0011
`define INST_EBREAK   12'b0000_0000_0001
`define HIT_GOOD_TRAP 1
`define HIT_BAD_TRAP  2
`define ABORT         3


// type
`define TYPE_BUS 2:0
`define INST_R   3'd1
`define INST_I   3'd2
`define INST_S   3'd3
`define INST_U   3'd4
`define INST_B   3'd5
`define INST_J   3'd6
`define INST_E   3'd7


// MUX1
`define MUX1_pc   1'b0
`define MUX1_src1 1'b1

// MUX2
`define MUX2_src2 1'b0
`define MUX2_imm  1'b1


// MUX3
`define MUX3_PCadd4 1'b0
`define MUX3_result 1'b1


// ALU
`define ADD     1'b1
`define AlucBus 0:0


// PC
`define RESET_VECTOR 32'h8000_0000
`define PC_INCREMENT 32'd4


// RegisterFile
`define RegRstVal 32'd0
`define RegBus    31:0
`define RegNum    32
`define Reg0      5'd0
`define Reg0_VAL  32'd0




