`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module register_file(
    input  wire           clk,
    input  wire           rst,
    input  wire           clk1_flag,
    input  wire           wen,
    input  wire [4:0]     rs1,
    input  wire [4:0]     rs2,
    input  wire [4:0]     rd,
    input  wire [`RegBus] rin,
    output wire [`RegBus] src1,
    output wire [`RegBus] src2
);

    integer i;
    reg[`RegBus] regs[`BitWidth-1 : 0];
    wire         r_wen;

    assign r_wen = (clk1_flag == 1'b1) & wen;

    //wire register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<`RegNum; i=i+1) begin
                regs[i] <= `RegRstVal;  
            end
        end else if((r_wen == 1'b1) && (rd != `Reg0))
            regs[rd] <= rin; 
        else
            regs[rd] <= regs[rd]; 
    end

    //read register
    assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule
