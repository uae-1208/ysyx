// reset
`define RST_VAL 1'b1


// R type instruction
`define INST_TYPE_R 7'b011_0011
`define INST_ADD    3'b000
`define INST_SUB    3'b000
`define INST_SLTU   3'b011
`define INST_XOR    3'b100
// `define INST_SRA    3'b101
`define INST_OR     3'b110


// I type instruction
`define INST_TYPE_I  7'b001_0011
`define INST_ADDI    3'b000
`define INST_SLTIU   3'b011
`define INST_SRLAI   3'b101


// L type instruction
`define INST_TYPE_L 7'b000_0011
`define INST_LW     3'b010


// S type instruction
`define INST_TYPE_S 7'b010_0011
`define INST_SH     3'b001
`define INST_SW     3'b010


// B type instruction
`define INST_TYPE_B 7'b110_0011
`define INST_BEQ    3'b000
`define INST_BNE    3'b001


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
`define Unit_ALU      0
`define Unit_CU1      1   //contril unit
`define Unit_CU2      2   
`define Unit_CU3      3   
`define Unit_CU4      4   
`define Unit_CU5      5   
`define Unit_CU6      6   
`define Unit_CU7      7   
`define Unit_CU8      8   
`define Unit_CU9      9   
`define Unit_CU10     10   
`define Unit_CU11     11   
`define Unit_CU12     12  
`define Unit_IE1      13   //imm extended unit
`define Unit_IE2      14  
`define Unit_IE3      15 


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


// MUX5
`define MUX6_PCadd4 1'b0
`define MUX6_bump   1'b1


// ALU
`define ADD       4'b0001
`define SUB       4'b0010
`define SLTU      4'b0011     //sltiu, sltu
`define XOR       4'b0100
`define SRA       4'b0101
`define OR        4'b0110
`define BEQ       4'b0111
`define BNE       4'b1000
`define ADD_JALR  4'b1001
`define AlucBus   3:0


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


