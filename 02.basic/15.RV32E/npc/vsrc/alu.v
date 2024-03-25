`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module alu(
    input  wire [`AlucBus] aluc,
    input  wire [`RegBus]  num1,
    input  wire [`RegBus]  num2,
    output reg  [`RegBus]  result
);

    wire [`RegBus] temp = {{(`BitWidth - 1){1'b1}}, 1'b0};  //for example, BitWidth = 32，then temp = 0xfffe

    always @(*) begin
        case (aluc)
            `ADD:      result = num1 + num2;
            `ADD_JALR: result = (num1 + num2) & temp;
            default:   result = num1 + num2;
        endcase
    end

endmodule
