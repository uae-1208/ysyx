`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module wbu(
    // system
    input  wire            clk,
    input  wire            rst,
    // shake hands
    input  wire            i_pre_valid,   //来自LSU，代表LSU的数据有效
    output wire            o_pre_ready,   //传递给LSU，代表WBU准备好处理新数据了
    output reg             o_cycle_end,   //传递给IFU，代表一个指令周期的结束，置位于第5时钟周期
    // from from from IFU
    input  wire [`CPU_Bus] i_wbu_pc,
    // from from from IDU
    input  wire [4:0]      i_wbu_rd_id,
    input  wire            i_wbu_gpr_wen,  
    // from from from Register File
    input  wire [`RegBus]  i_wbu_rs1,
    // from from from CSR Ctrl
    input  wire            i_wbu_is_mret,
    input  wire            i_wbu_is_ecall,
    input  wire [`CSR_Bus] i_wbu_csr_wid,
    input  wire [`RegBus]  i_wbu_csr_rd,
    input  wire            i_wbu_csr_wen,
    // from LSU
    input  wire [`RegBus]  i_wbu_rd,
    // to BRU
    output wire            o_wbu_npc_wen,
    // to Register File
    output wire [`RegBus]  o_wbu_rd,
    output wire [4:0]      o_wbu_rd_id,
    output wire            o_wbu_gpr_wen,
    // to CSR Ctrl
    output wire [`RegBus]  o_wbu_mcause_in,
    output wire [`RegBus]  o_wbu_mepc_in,
    output wire            o_wbu_csr_wen,  
    output wire [`CSR_Bus] o_wbu_csr_wid,
    output wire [`RegBus]  o_wbu_csr_rd
);

    // i_pre_valid --> ⌈‾‾‾‾‾⌉ --> o_cycle_end
    //                 | WBU |
    // o_pre_ready <-- ⌊_____⌋ 


    reg pre_valid_reg;
    always @(posedge clk) begin
        if(rst == 1'b1) 
            pre_valid_reg <= 1'b0;
        else
            pre_valid_reg <= i_pre_valid;
    end
    //复位时为1； 此外则是pre_valid_reg的上升沿检测。
    always @(posedge clk) begin
        if(rst == 1'b1) 
            o_cycle_end <= 1'b1;
        else
            o_cycle_end <= i_pre_valid & ~pre_valid_reg;
    end

    // to IFU
    assign o_pre_ready     = ~o_cycle_end;
    // to BRU
    assign o_wbu_npc_wen   = i_pre_valid & ~pre_valid_reg;    //只有效一周期，防止反复写入npc_reg
    // to Register File
    assign o_wbu_rd        = i_wbu_rd;
    assign o_wbu_rd_id     = i_wbu_rd_id;
    assign o_wbu_gpr_wen   = i_wbu_gpr_wen & o_wbu_npc_wen;    //只有效一周期，防止反复写入gpr
    // to CSR Ctrl
    assign o_wbu_mcause_in = i_wbu_rs1;
    assign o_wbu_mepc_in   = i_wbu_pc;
    assign o_wbu_csr_wen   = i_wbu_csr_wen;
    assign o_wbu_csr_wid   = i_wbu_csr_wid;
    assign o_wbu_csr_rd    = i_wbu_csr_rd;

endmodule
