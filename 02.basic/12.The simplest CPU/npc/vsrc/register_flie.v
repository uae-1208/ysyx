`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module register_file(
    input  wire           clk,
    input  wire           rst,
    input  wire           clk1_flag,
    input  wire [4:0]     rs1,
    input  wire [4:0]     rs2,
    input  wire [4:0]     rd,
    input  wire [`RegBus] result,
    output wire [`RegBus] src1,
    output wire [`RegBus] src2
);

    integer i;
    reg[`RegBus] regs[`RegNum-1 : 0];
    wire         wen;

    assign wen = (clk1_flag == 1'b1);

    //wire register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<32; i=i+1) begin
                regs[i] <= `RegRstVal;  
            end
        end else if((wen == 1'b1) && (rd != `Reg0))
            regs[rd] <= result; 
        else
            regs[rd] <= regs[rd]; 
    end

    //read register
    assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule
