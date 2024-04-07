// reset
`define RST_VAL 1'b1


// R type instruction
`define INST_TYPE_R 7'b011_0011
`define INST_ADD    3'b000
`define INST_SUB    3'b000
`define INST_SLL    3'b001
`define INST_SLTU   3'b011
`define INST_XOR    3'b100
`define INST_SRL    3'b101
`define INST_SRA    3'b101
`define INST_OR     3'b110
`define INST_AND    3'b111


// I type instruction
`define INST_TYPE_I  7'b001_0011
`define INST_ADDI    3'b000
`define INST_SLLI    3'b001
`define INST_SLTIU   3'b011
`define INST_XORI    3'b100
`define INST_SRLAI   3'b101
`define INST_ANDI    3'b111


// L type instruction
`define INST_TYPE_L 7'b000_0011
`define INST_LH     3'b001
`define INST_LW     3'b010
`define INST_LBU    3'b100
`define INST_LHU    3'b101


// S type instruction
`define INST_TYPE_S 7'b010_0011
`define INST_SB     3'b000
`define INST_SH     3'b001
`define INST_SW     3'b010


// B type instruction
`define INST_TYPE_B 7'b110_0011
`define INST_BEQ    3'b000
`define INST_BNE    3'b001
`define INST_BLT    3'b100
`define INST_BGE    3'b101
`define INST_BLTU   3'b110
`define INST_BGEU   3'b111


// U type instruction
`define INST_TYPE_LUI   7'b011_0111
`define INST_TYPE_AUIPC 7'b001_0111


// JALR type instruction
`define INST_TYPE_JALR 7'b110_0111
// JAL type instruction
`define INST_TYPE_JAL  7'b110_1111


// E type instruction
`define INST_TYPE_E   7'b111_0011
`define INST_EBREAK   12'b0000_0000_0001
`define HIT_TRAP      1
`define ABORT         2
`define Unit_ALU      0   //alu
`define Unit_MEM      1   //memory
`define Unit_CU1      2   //contril unit
`define Unit_CU2      3   
`define Unit_CU3      4   
`define Unit_CU4      5   
`define Unit_CU5      6   
`define Unit_CU6      7   
`define Unit_CU7      8   
`define Unit_CU8      9   
`define Unit_CU9      10   
`define Unit_CU10     11   
`define Unit_CU11     12   
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
`define MUX1_NBpc  1'b0   //not bump inst
`define MUX1_Bpc   1'b1   //is bump inst


// MUX2
`define MUX2_PCadd4  1'b0
`define MUX2_result  1'b1

// MUX3
`define MUX3_src2  1'b0
`define MUX3_imm32 1'b1

// MUX4
`define MUX4_pc    1'b0
`define MUX4_src1  1'b1

// MUX5
`define MUX5_PCadd4 2'd0
`define MUX5_memdat 2'd1
`define MUX5_result 2'd2
`define MUX5_IDLE   2'd3



// ALU
`define ADD       5'b00000
`define SUB       5'b00001
`define SLL       5'b00010
`define XOR       5'b00011
`define SRL       5'b00100
`define SRA       5'b00101
`define OR        5'b00110
`define AND       5'b00111
`define EQ        5'b01000
`define NE        5'b01001
`define LT        5'b01010
`define GE        5'b01011
`define LTU       5'b01100
`define GEU       5'b01101
`define ADD_LUI   5'b01110
`define ADD_JALR  5'b01111
`define AlucBus   4:0


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
`define LoadW     3'd0
`define LoadBU    3'd1
`define LoadHU    3'd2
`define LoadB     3'd3
`define LoadH     3'd4


// ARCH
`define BitWidth  32
`define RegNum    32
`define RegBus    31:0
`define RegRstVal 32'd0


