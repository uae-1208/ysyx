`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"
`define LSU_PKG_WDITH (`CPU_Width+`CPU_Width+`CPU_Width+1+1+1+`CPU_Width+1+`CPU_Width+5+1+1+1+1+12+`CPU_Width)

module lsu(
    // system
    input  wire            clk,
    input  wire            rst,
    // shake hands
    input  wire            i_pre_valid,   //来自EXU，代表EXU的数据有效
    output wire            o_pre_ready,   //传递给WBU，代表LSU准备好处理新数据了
    output wire            o_post_valid,  //传递给WBU，代表此时数据包寄存器的数据有效
    input  wire            i_post_ready,  //来自WBU，代表WBU准备好处理新数据了
    // from from from IFU
    input  wire [`CPU_Bus] i_lsu_pc,
    // from from IDU
    input  wire            i_lsu_is_load,
    input  wire            i_lsu_is_store,
    input  wire [2:0]      i_lsu_func3,
    input  wire [`CPU_Bus] i_lsu_imm,
    input  wire            i_lsu_is_jal,
    input  wire            i_lsu_is_jalr,
    input  wire            i_lsu_brch,
    input  wire [4:0]      i_lsu_rd_id,
    input  wire            i_lsu_gpr_wen,  
    // from from Register File
    input  wire [`RegBus]  i_lsu_rs1,
    input  wire [`RegBus]  i_lsu_rs2,
    // from from CSR Ctrl
    input  wire [`CPU_Bus] i_lsu_csr_npc,
    input  wire [`CSR_Bus] i_lsu_csr_wid,
    input  wire [`RegBus]  i_lsu_csr_rd,
    input  wire            i_lsu_csr_wen,  
    input  wire            i_lsu_is_mret,
    input  wire            i_lsu_is_ecall,
    // from EXU
    input  wire [`CPU_Bus] i_lsu_exu_res,
    // to BRU
    output wire [`CPU_Bus] o_lsu_imm,
    output wire [`CPU_Bus] o_lsu_pc,
    output wire [`RegBus]  o_lsu_rs1,
    output wire            o_lsu_is_jal,
    output wire            o_lsu_is_jalr,
    output wire            o_lsu_brch,    
    output wire [`CPU_Bus] o_lsu_csr_npc,
    output wire            o_lsu_is_ejump,  // exception jump    
    // to WEU
    output wire [`RegBus]  o_lsu_rd,
    output wire [4:0]      o_lsu_rd_id,
    output wire            o_lsu_gpr_wen,
    output wire            o_lsu_csr_wen,
    output wire            o_lsu_is_mret,
    output wire            o_lsu_is_ecall,
    output wire [`CSR_Bus] o_lsu_csr_wid,
    output wire [`RegBus]  o_lsu_csr_rd
);

    import "DPI-C" function int  dmem_read(input int raddr);
    import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);
    import "DPI-C" function void TRAP(input int station, input byte unit);


    //lsu_reg_wen  = i_pre_valid & o_pre_ready
    //o_post_valid = i_pre_valid 延迟一周期
    //o_pre_ready  = ~o_post_valid
    // i_pre_valid --> ⌈‾‾‾‾‾⌉ --> o_post_valid
    //                 | LSU |
    // o_pre_ready <-- ⌊_____⌋ <-- i_post_ready



    /************ data package ************/
    // to BRU
    wire [`CPU_Bus] lsu_imm      = i_lsu_imm;
    wire [`CPU_Bus] lsu_pc       = i_lsu_pc; 
    wire [`RegBus]  lsu_rs1      = i_lsu_rs1; 
    wire            lsu_is_jal   = i_lsu_is_jal;
    wire            lsu_is_jalr  = i_lsu_is_jalr;
    wire            lsu_brch     = i_lsu_brch;
    wire [`CPU_Bus] lsu_csr_npc  = i_lsu_csr_npc;
    wire            lsu_is_ejump = i_lsu_is_mret | i_lsu_is_ecall; 
    // to WEU
    wire [`CPU_Bus] lsu_rd;
    wire [4:0]      lsu_rd_id    = i_lsu_rd_id;
    wire            lsu_gpr_wen  = i_lsu_gpr_wen;  
    wire            lsu_csr_wen  = i_lsu_csr_wen;
    wire            lsu_is_mret  = i_lsu_is_mret;
    wire            lsu_is_ecall = i_lsu_is_ecall;
    wire [`CSR_Bus] lsu_csr_wid  = i_lsu_csr_wid;
    wire [`CPU_Bus] lsu_csr_rd   = i_lsu_csr_rd;


    /************ read dmem ************/
    wire [`CPU_Bus] dmem_raddr   = i_lsu_exu_res;
    reg  [`CPU_Bus] dmem_rdata_t;
    reg  [`CPU_Bus] dmem_rdata;
    // 有读请求时
    always @(*) begin
        if(i_lsu_is_load == `TRUE)  // 有读请求时
            dmem_rdata_t = dmem_read(dmem_raddr);
        else
            dmem_rdata_t = 32'h00000001;
    end    

    // dmem_rdata_t -> rdata
    always @(*) begin
        dmem_rdata = `CPU_Width'd0;
        if(i_lsu_is_load == `TRUE)  begin// 有读请求时
            case (i_lsu_func3)
                `INST_LBU:  dmem_rdata = {24'd0, dmem_rdata_t[7:0]};
                `INST_LHU:  dmem_rdata = {16'd0, dmem_rdata_t[15:0]};
                `INST_LB:   dmem_rdata = {{24{dmem_rdata_t[7]}}, dmem_rdata_t[7:0]};
                `INST_LH:   dmem_rdata = {{16{dmem_rdata_t[15]}}, dmem_rdata_t[15:0]};
                `INST_LW:   dmem_rdata = dmem_rdata_t;
                default:    TRAP(`ABORT, `Unit_LSU1);  //uae
            endcase
        end
    end            
    assign lsu_rd = (i_lsu_is_load == `TRUE) ? dmem_rdata : i_lsu_exu_res;  // Its load inst(1'b1) or not (1'b0)



    /************ write dmem ************/
    wire [`CPU_Bus] dmem_waddr = i_lsu_exu_res;
    wire [`CPU_Bus] dmem_wdata = i_lsu_rs2;
    reg  [7:0]    wmask;
    // wmask
    always @(*) begin
        if(i_lsu_is_store == `TRUE) begin // 有写请求时
            case (i_lsu_func3)
                `INST_SB: wmask = `WByte;
                `INST_SH: wmask = `WHalf;
                `INST_SW: wmask = `WWord;
                default:  TRAP(`ABORT, `Unit_LSU2);  //uae
            endcase
        end
    end  

    always @(*) begin
        if(i_lsu_is_store == `TRUE) begin // 有写请求时
            pmem_write(dmem_waddr, dmem_wdata, wmask);
        end
    end



    // data package
    wire         lsu_reg_wen  = i_pre_valid & o_pre_ready;   //数据包寄存器的写使能
    reg  [`LSU_PKG_WDITH-1 : 0] lsu_valid_data_reg;  
    always @(posedge clk) begin
        if(rst == 1'b1) 
            lsu_valid_data_reg <= 0;
        else if(lsu_reg_wen == 1'b1)
            lsu_valid_data_reg <= { lsu_imm, lsu_pc, lsu_rs1, lsu_is_jal, lsu_is_jalr, lsu_brch, 
                                    lsu_csr_npc, lsu_is_ejump, lsu_rd, lsu_rd_id, lsu_gpr_wen, 
                                    lsu_csr_wen, lsu_is_mret, lsu_is_ecall, lsu_csr_wid, lsu_csr_rd };
    end

    assign{ o_lsu_imm, o_lsu_pc, o_lsu_rs1, o_lsu_is_jal, o_lsu_is_jalr, o_lsu_brch, 
            o_lsu_csr_npc, o_lsu_is_ejump, o_lsu_rd, o_lsu_rd_id, o_lsu_gpr_wen, 
            o_lsu_csr_wen, o_lsu_is_mret, o_lsu_is_ecall, o_lsu_csr_wid, o_lsu_csr_rd } = lsu_valid_data_reg;



    // shake hands
    reg post_valid_reg;
    always @(posedge clk) begin
        if(rst == 1'b1) 
            post_valid_reg <= 1'h0;
        else
            post_valid_reg <= i_pre_valid;
    end
    assign o_post_valid = post_valid_reg;
    assign o_pre_ready  = ~o_post_valid;

endmodule
