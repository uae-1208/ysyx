`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module alu(
    input  wire [`AlucBus] aluc,
    input  wire [`RegBus]  num1,
    input  wire [`RegBus]  num2,
    output reg  [`RegBus]  result
);

    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);
    
    wire [`RegBus] temp = {{(`BitWidth - 1){1'b1}}, 1'b0};  //for example, BitWidth = 32，then temp = 0xfffe
    wire [`RegBus] num1_cplm = ~num1 + `RegNum'h1;    //complement code
    wire [`RegBus] num2_cplm = ~num2 + `RegNum'h1;    //complement code

    always @(*) begin
        case (aluc)
            `ADD:      result = num1 + num2;
            `SUB:      result = num1 - num2_cplm;
            `ADD_JALR: result = (num1 + num2) & temp;
            default:   ebreak(`ABORT, 32'hdeafbeaf, `Unit_ALU);
        endcase
    end

endmodule
