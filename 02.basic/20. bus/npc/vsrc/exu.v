`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"
`define EXU_PKG_WDITH  (`CPU_Width+1+1+3+`CPU_Width+`CPU_Width+`CPU_Width+`CPU_Width+1+1+1+5+1)

module exu(
    // system
    input  wire            clk,
    input  wire            rst,
    // shake hands
    input  wire            i_pre_valid,   //来自IDU，代表IDU的数据有效
    output wire            o_pre_ready,   //传递给LSU，代表EXU准备好处理新数据了
    output wire            o_post_valid,  //传递给LSU，代表此时数据包寄存器的数据有效
    input  wire            i_post_ready,  //来自LSU，代表LSU准备好处理新数据了
    // from from IFU
    input  wire [`CPU_Bus] i_exu_pc,
    // from IDU
    input  wire [`ALU_Bus] i_exu_alu_type,
    input  wire [1:0]      i_exu_num_sel,
    input  wire [`CPU_Bus] i_exu_imm,
    input  wire            i_exu_is_jal,
    input  wire            i_exu_is_jalr,
    input  wire            i_exu_is_brch,
    input  wire            i_exu_is_load,
    input  wire            i_exu_is_store,
    input  wire [2:0]      i_exu_func3,
    input  wire [4:0]      i_exu_rd_id,
    input  wire            i_exu_gpr_wen,  
    // from Register File
    input  wire [`RegBus]  i_exu_rs1,
    input  wire [`RegBus]  i_exu_rs2,
    // to LSU
    output wire [`CPU_Bus] o_exu_alu_res,
    output wire            o_exu_is_load,
    output wire            o_exu_is_store,
    output wire [2:0]      o_exu_func3,
    output wire [`CPU_Bus] o_exu_rs1,
    output wire [`CPU_Bus] o_exu_rs2,
    // to to BRU
    output wire [`CPU_Bus] o_exu_imm,
    output wire [`CPU_Bus] o_exu_pc,
    output wire            o_exu_is_jal,
    output wire            o_exu_is_jalr,
    output wire            o_exu_brch,
    // to to WEU
    output wire [4:0]      o_exu_rd_id,
    output wire            o_exu_gpr_wen
);


    import "DPI-C" function void TRAP(input int station, input byte unit);

    //exu_reg_wen  = i_pre_valid & o_pre_ready
    //o_post_valid = i_pre_valid 延迟一周期
    //o_pre_ready  = ~o_post_valid
    // i_pre_valid --> ⌈‾‾‾‾‾⌉ --> o_post_valid
    //                 | EXU |
    // o_pre_ready <-- ⌊_____⌋ <-- i_post_ready



    /************ data package ************/
    // to LSU
    reg  [`CPU_Bus] exu_alu_res;
    wire            exu_is_load  = i_exu_is_load;
    wire            exu_is_store = i_exu_is_store;
    wire [2:0]      exu_func3    = i_exu_func3;
    wire [`CPU_Bus] exu_rs1      = i_exu_rs1;
    wire [`CPU_Bus] exu_rs2      = i_exu_rs2;
    // to to BRU
    wire [`CPU_Bus] exu_imm      = i_exu_imm;
    wire [`CPU_Bus] exu_pc       = i_exu_pc;
    wire            exu_is_jal   = i_exu_is_jal;
    wire            exu_is_jalr  = i_exu_is_jalr;
    wire            exu_brch     = i_exu_is_brch & exu_alu_res[0];  //check if is branch inst while branch condition is true
    // to to WEU
    wire [4:0]      exu_rd_id    = i_exu_rd_id;
    wire            exu_gpr_wen  = i_exu_gpr_wen;


    MuxKey #(4, 2, `CPU_Width) mux1(num1, i_exu_num_sel, {
        `RS1_RS2, i_exu_rs1,
        `RS1_IMM, i_exu_rs1,
        `PC_IMM,  i_exu_pc,
        `PC_4,    i_exu_pc}       
    );

    MuxKey #(4, 2, `CPU_Width) mux2(num2, i_exu_num_sel, {
        `RS1_RS2, i_exu_rs2,
        `RS1_IMM, i_exu_imm,
        `PC_IMM,  i_exu_imm,
        `PC_4,    `CPU_Width'd4}       
    );

    // alu
    wire [`CPU_Bus] num1, num2;
    wire [`CPU_Bus] num2_cplm = ~num2 + `CPU_Width'h1;   // 补码
    always @(*) begin
        exu_alu_res = `CPU_Width'd0;
        case (i_exu_alu_type)
            `ALU_ADD:   exu_alu_res = num1 + num2;
            `ALU_SUB:   exu_alu_res = num1 + num2_cplm;
            `ALU_SLL:   exu_alu_res = num1 << num2[4:0];
            `ALU_XOR:   exu_alu_res = num1 ^ num2;
            `ALU_SRL:   exu_alu_res = num1 >> num2[4:0];
            `ALU_SRA:   exu_alu_res = ($signed(num1)) >>> num2[4:0];
            `ALU_OR:    exu_alu_res = num1 | num2;
            `ALU_AND:   exu_alu_res = num1 & num2;
            `ALU_EQ:    exu_alu_res = {{(`CPU_Width - 1){1'b0}}, (num1 == num2)};
            `ALU_NE:    exu_alu_res = {{(`CPU_Width - 1){1'b0}}, (num1 != num2)};
            `ALU_LT:    exu_alu_res = {{(`CPU_Width - 1){1'b0}}, (($signed(num1)) <  ($signed(num2)))};
            `ALU_GE:    exu_alu_res = {{(`CPU_Width - 1){1'b0}}, (($signed(num1)) >= ($signed(num2)))};
            `ALU_LTU:   exu_alu_res = {{(`CPU_Width - 1){1'b0}}, (num1 <  num2)};
            `ALU_GEU:   exu_alu_res = {{(`CPU_Width - 1){1'b0}}, (num1 >= num2)};
            default:    TRAP(`ABORT, `Unit_EXU1);  //uae
        endcase
    end
    

    // data package
    wire exu_reg_wen  = i_pre_valid & o_pre_ready;   //数据包寄存器的写使能
    reg  [`EXU_PKG_WDITH-1 : 0] exu_valid_data_reg;  
    always @(posedge clk) begin
        if(rst == 1'b1) 
            exu_valid_data_reg <= 0;
        else if(exu_reg_wen == 1'b1)
            exu_valid_data_reg <= { exu_alu_res, exu_is_load, exu_is_store, exu_func3,
                                    exu_rs1, exu_rs2, exu_imm, exu_pc, exu_is_jal,
                                    exu_is_jalr, exu_brch, exu_rd_id, exu_gpr_wen };
    end

    assign{ o_exu_alu_res, o_exu_is_load, o_exu_is_store, o_exu_func3,
            o_exu_rs1, o_exu_rs2, o_exu_imm, o_exu_pc, o_exu_is_jal,
            o_exu_is_jalr, o_exu_brch, o_exu_rd_id, o_exu_gpr_wen } = exu_valid_data_reg;



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