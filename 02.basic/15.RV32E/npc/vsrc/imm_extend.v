`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module RISB_type(
    input  wire [4:0]       rs2,
    input  wire [6:0]       funct7,
    input  wire [`TYPE_BUS] type2,
    output reg  [11:0]      imm_12
);
    always @(*) begin
        case (type2)
            // `INST_R: imm_12 = 12'b0000_0000_0000;
            `INST_I: imm_12 = {funct7, rs2};
            //`INST_S: imm_12 = {funct7, rd};
            //`INST_B: imm_12 = {funct7[6], rd[0], funct7[5:0], rd[4:1]};
            default:imm_12 = 12'b0000_0000_0000; 
        endcase
    end
endmodule

module UJ_type(
    input  wire [4:0]       rs1,
    input  wire [4:0]       rs2,
    input  wire [2:0]       funct3,
    input  wire [6:0]       funct7,
    input  wire [`TYPE_BUS] type2,
    output reg  [19:0]      imm_20
);
    always @(*) begin
        case (type2)
            `INST_U: imm_20 = {funct7, rs2, rs1, funct3} << 12;
            // `INST_J: imm_20 = {funct7, rs2};
            default:imm_20 = 20'b0000_0000_0000_0000_0000; 
        endcase
    end
endmodule

module Extend_12(
    input  wire [11:0]    imm_12,
    output wire [`RegBus] imm_12_to_32
);
    assign imm_12_to_32 = {{20{imm_12[11]}}, imm_12};
endmodule

module Extend_20(
    input  wire [19:0]    imm_20,
    output wire [`RegBus] imm_20_to_32
);
    assign imm_20_to_32 = {{12{imm_20[19]}}, imm_20};
endmodule


module imm_extend(
    input  wire [4:0]       rs1,
    input  wire [4:0]       rs2,
    input  wire [2:0]       funct3,
    input  wire [6:0]       funct7,
    input  wire [`TYPE_BUS] type3,
    output reg  [`RegBus]   imm32
);

    wire[11:0]    imm_12;
    wire[19:0]    imm_20;
    wire[`RegBus] imm_12_to_32;
    wire[`RegBus] imm_20_to_32;

    RISB_type RISB_type_inst(
        .rs2   (rs2),
        .funct7(funct7),
        .type2 (type3),
        .imm_12(imm_12)
    );

    UJ_type UJ_type_inst(
        .rs1   (rs1),
        .rs2   (rs2),
        .funct3(funct3),
        .funct7(funct7),
        .type2 (type3),
        .imm_20(imm_20)
    );

    Extend_12 Extend_12_inst(
        .imm_12      (imm_12),
        .imm_12_to_32(imm_12_to_32)
    );

    Extend_20 Extend_20_inst(
        .imm_20      (imm_20),
        .imm_20_to_32(imm_20_to_32)
    );

    always @(*) begin
        case (type3)
            `INST_I: imm32 = imm_12_to_32;
            `INST_U: imm32 = imm_20_to_32;
            default: imm32 = 32'd0;
        endcase
    end
endmodule
