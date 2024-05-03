`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module bru(
    // system
    input  wire            clk,
    input  wire            rst,
    // from from from from IFU
    input  wire [`CPU_Bus] i_bru_pc,
    // from from from IFU
    input  wire [`CPU_Bus] i_bru_imm,
    input  wire            i_bru_is_jal,
    input  wire            i_bru_is_jalr,
    input  wire            i_bru_brch,
    // from from from Register File
    input  wire [`RegBus]  i_bru_rs1,
    // from WBU
    input  wire            i_bru_npc_wen,
    // to IFU
    output wire [`CPU_Bus] o_bru_npc
);
    
    wire [`CPU_Bus] pc_jorb;
    wire [`CPU_Bus] npc_r;
    wire [`RegBus]  temp = {{(`CPU_Width - 1){1'b1}}, 1'b0};  //for example, CPU_Width = 32，then temp = 0xfffe
    
    MuxKey #(2, 1, `CPU_Width) mux1(pc_jorb, i_bru_is_jalr, {
        `FALSE, i_bru_pc + i_bru_imm,               // jal or branch instruction
        `TRUE,  (i_bru_rs1 + i_bru_imm) & temp}     // jalr
    );

    MuxKey #(2, 1, `CPU_Width) mux2(npc_r, (i_bru_is_jalr | i_bru_is_jal | i_bru_brch), {
        `FALSE, i_bru_pc + `CPU_Width'h4,           // pc + 4        
        `TRUE,  pc_jorb}                            // jalr pr jal or branch instruction
    );

    reg [`CPU_Bus] npc_reg;
    always @(posedge clk) begin
        if(rst == 1'b1) 
            npc_reg <= `RESET_VECTOR;
        else if(i_bru_npc_wen == 1'b1)
            npc_reg <= npc_r;
    end
    assign o_bru_npc = npc_reg;

endmodule
