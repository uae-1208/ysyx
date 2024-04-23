`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module register_file(
    input  wire           clk,
    input  wire           rst,
    input  wire           is_ecall,
    input  wire           reg_wen,
    input  wire [4:0]     rs1,
    input  wire [4:0]     rs2,
    input  wire [4:0]     rd,
    input  wire [`RegBus] reg_in,
    output wire [`RegBus] src1,
    output wire [`RegBus] src2
);

    integer i;
    reg [`RegBus] regs[`BitWidth-1 : 0];
    wire[`RegBus] src1_temp;

    //write register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<`RegNum; i=i+1) begin
                regs[i] <= `RegRstVal;  
            end
        end else if((reg_wen == 1'b1) && (rd != `Reg0))
            regs[rd] <= reg_in; 
        else
            regs[rd] <= regs[rd]; 
    end

    //read register
    // assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src1_temp = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src1 = (is_ecall == 1'b1) ? regs[`Mcause_gpr] : src1_temp;
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule
