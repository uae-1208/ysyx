// reset
`define RST_VAL 1'b1


// R type instruction
`define INST_TYPE_R 7'b011_0011
`define INST_ADD    3'b000
`define INST_SUB    3'b000


// I type instruction
`define INST_TYPE_I 7'b001_0011
`define INST_ADDI   3'b000


// L type instruction
`define INST_TYPE_L 7'b000_0011
`define INST_LW     3'b010


// S type instruction
`define INST_TYPE_S 7'b010_0011
`define INST_SW     3'b010


// U type instruction
`define INST_TYPE_AUIPC 7'b001_0111


// JALR type instruction
`define INST_TYPE_JALR 7'b110_0111
// JAL type instruction
`define INST_TYPE_JAL   7'b110_1111


// E type instruction
`define INST_TYPE_E   7'b111_0011
`define INST_EBREAK   12'b0000_0000_0001
`define HIT_TRAP      1
`define ABORT         2
`define Unit_ALU      1
`define Unit_CU       2   //contril unit
`define Unit_IE       3   //imm extended unit

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


// MUX4
`define MUX4_PCadd4 2'd0
`define MUX4_result 2'd1
`define MUX4_memdat 2'd2
`define MUX4_IDLE   2'd3


// MUX5
`define MUX5_pc     1'b0
`define MUX5_result 1'b1


// ALU
`define ADD       2'b01
`define SUB       2'b10
`define ADD_JALR  2'b11
`define AlucBus   1:0


// PC
`define RESET_VECTOR 32'h8000_0000
`define PC_INCREMENT 32'd4


// RegisterFile
`define Reg0      5'd0
`define Reg0_VAL  32'd0
`define WDisen    1'b0
`define WEnable   1'b1


// mem
`define WDisen    1'b0
`define WEnable   1'b1
`define WByte     8'b0000_0001
`define WHalf     8'b0000_0011
`define WWord     8'b0000_1111


// ARCH
`define BitWidth  32
`define RegNum    32
`define RegBus    31:0
`define RegRstVal 32'd0


