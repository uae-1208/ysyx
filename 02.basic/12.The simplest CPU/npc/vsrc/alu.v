`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module alu(
    input  wire           aluc,
    input  wire [`RegBus] num1,
    input  wire [`RegBus] num2,
    output reg  [`RegBus] result
);

    always @(*) begin
        case (aluc)
            `ADD:    result = num1 + num2;
            default: result = num1 + num2;
        endcase
    end

endmodule
