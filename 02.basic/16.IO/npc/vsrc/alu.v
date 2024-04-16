`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module alu(
    input  wire [`AlucBus] aluc,
    input  wire [`RegBus]  num1,
    input  wire [`RegBus]  num2,
    output reg  [`RegBus]  result
);

    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);
    
    wire [`RegBus] temp = {{(`BitWidth - 1){1'b1}}, 1'b0};  //for example, BitWidth = 32，then temp = 0xfffe
    // wire [`RegBus] num1_cplm = ~num1 + `RegNum'h1;    //complement code
    wire [`RegBus] num2_cplm = ~num2 + `RegNum'h1;    //complement code
    wire [`RegBus] num2_temp = (num2 & 32'h1f);    

    always @(*) begin
        case (aluc)
            `ADD:      result = num1 + num2;
            `SUB:      result = num1 + num2_cplm;
            `SLL:      result = num1 << num2;
            `XOR:      result = num1 ^ num2;
            `SRL:      result = num1 >> (num2 & 32'h1f);
            `SRA:      result = ($signed(num1)) >>> (num2 & 32'h1f);
            `OR:       result = num1 | num2;
            `AND:      result = num1 & num2;
            `EQ:       result = {{(`BitWidth - 1){1'b0}}, (num1 == num2)};
            `NE:       result = {{(`BitWidth - 1){1'b0}}, (num1 != num2)};
            `LT:       result = {{(`BitWidth - 1){1'b0}}, (($signed(num1)) <  ($signed(num2)))};
            `GE:       result = {{(`BitWidth - 1){1'b0}}, (($signed(num1)) >= ($signed(num2)))};
            `LTU:      result = {{(`BitWidth - 1){1'b0}}, (num1 <  num2)};
            `GEU:      result = {{(`BitWidth - 1){1'b0}}, (num1 >= num2)};
            `ADD_LUI:  result = num2;
            `ADD_JALR: result = (num1 + num2) & temp;
            default:   begin
                        ebreak(`ABORT, 32'hdeafbeaf, `Unit_ALU);
                        result = 0;
                       end
        endcase
    end

endmodule
