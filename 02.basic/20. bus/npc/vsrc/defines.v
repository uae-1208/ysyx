// reset
`define RST_VAL 1'b1


// R type instruction
`define TYPE_R        7'b011_0011
`define INST_ADD_SUB  3'b000
`define INST_SLL      3'b001
`define INST_SLT      3'b010
`define INST_SLTU     3'b011
`define INST_XOR      3'b100
`define INST_SRL_SRA  3'b101
`define INST_OR       3'b110
`define INST_AND      3'b111


// I type instruction
`define TYPE_I       7'b001_0011
`define INST_ADDI    3'b000
`define INST_SLLI    3'b001
`define INST_SLTI    3'b010
`define INST_SLTIU   3'b011
`define INST_XORI    3'b100
`define INST_ORI     3'b110
`define INST_SRLAI   3'b101
`define INST_ANDI    3'b111


// L type instruction
`define TYPE_I_LOAD 7'b000_0011
`define INST_LB     3'b000
`define INST_LH     3'b001
`define INST_LW     3'b010
`define INST_LBU    3'b100
`define INST_LHU    3'b101


// S type instruction
`define TYPE_STORE  7'b010_0011
`define INST_SB     3'b000
`define INST_SH     3'b001
`define INST_SW     3'b010


// B type instruction
`define TYPE_B      7'b110_0011
`define INST_BEQ    3'b000
`define INST_BNE    3'b001
`define INST_BLT    3'b100
`define INST_BGE    3'b101
`define INST_BLTU   3'b110
`define INST_BGEU   3'b111


// U type instruction
`define TYPE_U_LUI   7'b011_0111
`define TYPE_U_AUIPC 7'b001_0111


// JALR type instruction
`define TYPE_I_JALR  7'b110_0111
// JAL type instruction
`define TYPE_JAL     7'b110_1111


// E type instruction
`define TYPE_E   7'b111_0011
`define INST_CSRRW    3'b001
`define INST_CSRRS    3'b010
`define INST_MRET     12'b0011_0000_0010
`define INST_ECALL    12'b0000_0000_0000
`define INST_EBREAK   12'b0000_0000_0001
`define HIT_TRAP      1
`define ABORT         2
`define Unit_IDU1     0  
`define Unit_IDU2     1   
`define Unit_IDU3     2  
`define Unit_IDU4     3   
`define Unit_IDU5     4   
`define Unit_IDU6     5   
`define Unit_EXU1     6   
`define Unit_LSU1     7   
`define Unit_LSU2     8   




// ALU operation type
`define ALU_ADD   4'b0000
`define ALU_SUB   4'b0001
`define ALU_SLL   4'b0010
`define ALU_XOR   4'b0011
`define ALU_SRL   4'b0100
`define ALU_SRA   4'b0101
`define ALU_OR    4'b0110
`define ALU_AND   4'b0111
`define ALU_EQ    4'b1000
`define ALU_NE    4'b1001
`define ALU_LT    4'b1010
`define ALU_GE    4'b1011
`define ALU_LTU   4'b1100
`define ALU_GEU   4'b1101
`define ALU_Bus   3:0
`define ALU_Width 4

// ALU operators
`define RS1_RS2  2'b00
`define RS1_IMM  2'b01
`define PC_IMM   2'b10
`define PC_4     2'b11


// PC
`define RESET_VECTOR 32'h8000_0000
`define PC_INCREMENT 32'd4


// RegisterFile
`define Reg_x0     5'd0
`define Reg0_VAL   32'd0
`define WDisen     1'b0
`define WEnable    1'b1
`define Mcause_gpr 15  // riscve : a5 ; others a7


// memory
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
`define CPU_Width  32
`define CPU_Bus    31:0
`define RegNum     32
`define RegBus     31:0
`define RegRstVal  32'd0


// Logic
`define TRUE  1'b1
`define FALSE 1'b0


