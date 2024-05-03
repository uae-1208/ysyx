`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module wbu(
    // system
    input  wire            clk,
    input  wire            rst,
    // shake hands
    input  wire            i_pre_valid,   //来自LSU，代表LSU的数据有效
    output wire            o_pre_ready,   //传递给LSU，代表WBU准备好处理新数据了
    output reg             o_cycle_end,   //传递给IFU，代表一个指令周期的结束，置位于第5时钟周期
    // from from from IDU
    input  wire [4:0]      i_wbu_rd_id,
    input  wire            i_wbu_gpr_wen,  
    // from LSU
    input  wire [`CPU_Bus] i_wbu_rd,
    // to BRU
    output wire            o_wbu_npc_wen,
    // to Register File
    output wire [`CPU_Bus] o_wbu_rd,
    output wire [4:0]      o_wbu_rd_id,
    output wire            o_wbu_gpr_wen
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

    // to LSU
    assign o_pre_ready = ~o_cycle_end;
    // to BRU
    assign o_wbu_npc_wen = i_pre_valid & ~pre_valid_reg;    //只有效一周期，防止反复写入npc_reg
    // to Register File
    assign o_wbu_rd      = i_wbu_rd;
    assign o_wbu_rd_id   = i_wbu_rd_id;
    assign o_wbu_gpr_wen = i_wbu_gpr_wen & o_wbu_npc_wen;    //只有效一周期，防止反复写入gpr
    
endmodule

