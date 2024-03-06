`include "defines.v"

module RISB_type(
    input  wire [4:0]       rs2,
    input  wire [6:0]       funct7,
    input  wire [`TYPE_BUS] type,
    output reg  [11:0]      imm_12
);
    always @(*) begin
        case (type)
            `INST_R: imm_12 = 12'b0000_0000_0000;
            `INST_I: imm_12 = {funct7, rs2};
            //`INST_S: imm_12 = {funct7, rd};
            //`INST_B: imm_12 = {funct7[6], rd[0], funct7[5:0], rd[4:1]};
            default:imm_12 = 12'b0000_0000_0000; 
        endcase
    end
endmodule

module Extend_12(
    input  wire [11:0]    imm_12,
    output wire [`RegBus] imm_12_to_32
);
    assign imm_12_to_32 = {{20{imm_12[11]}}, imm_12};
endmodule

/*module Extend_20(
    input  wire [19:0]    imm_20,
    output wire [`RegBus] imm_20_to_32
);
    assign imm_20_to_32 = {{12{imm_20[19]}}, imm_20};
endmodule*/


module imm_extend(
    input  wire [4:0]       rs2,
    input  wire [6:0]       funct7,
    input  wire [`TYPE_BUS] type,
    output wire [`RegBus]   imm32
);

    wire[11:0] imm_12;

    RISB_type RISB_type_inst(
        .rs2   (rs2),
        .funct7(funct7),
        .type  (type),
        .imm_12(imm_12)
    );

    Extend_12 Extend_12_inst(
        .imm_12      (imm_12),
        //.imm_12_to_32(imm_12_to_32)
        .imm_12_to_32(imm32)
    );

    /*Extend_20 Extend_20_inst(
        .imm_20      (imm_20),
        .imm_20_to_32(imm_20_to_32)
    );*/
endmodule
