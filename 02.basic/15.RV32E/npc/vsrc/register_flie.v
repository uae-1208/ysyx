`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module register_file(
    input  wire           clk,
    input  wire           rst,
    input  wire           wen_reg,
    input  wire [4:0]     rs1,
    input  wire [4:0]     rs2,
    input  wire [4:0]     rd,
    input  wire [`RegBus] rin,
    output wire [`RegBus] src1,
    output wire [`RegBus] src2
);

    integer i;
    reg[`RegBus] regs[`BitWidth-1 : 0];
    wire         wen;

    assign wen = wen_reg;

    //wire register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<`RegNum; i=i+1) begin
                regs[i] <= `RegRstVal;  
            end
        end else if((wen == 1'b1) && (rd != `Reg0))
            regs[rd] <= rin; 
        else
            regs[rd] <= regs[rd]; 
    end

    //read register
    assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule
