`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"
`define IDU_PKG_WDITH  (5+5+12+1+1+1+2+`ALU_Width+2+`CPU_Width+1+1+3+`CPU_Width+1+1+1+5+1)

module idu(
    // system
    input  wire            clk,
    input  wire            rst,
    // shake hands
    input  wire            i_pre_valid,   //来自IFU，代表IFU的数据有效
    output wire            o_pre_ready,   //传递给EXU，代表IDU准备好处理新数据了
    output wire            o_post_valid,  //传递给EXU，代表此时数据包寄存器的数据有效
    input  wire            i_post_ready,  //来自EXU，代表EXU准备好处理新数据了
    // from IFU
    input  wire [`CPU_Bus] i_idu_pc,
    input  wire [`CPU_Bus] i_idu_inst,
    // to Register File
    output wire [4:0]      o_idu_rs_id1,
    output wire [4:0]      o_idu_rs_id2,
    // to CSR Ctrl
    output wire [`CSR_Bus] o_idu_csr_rid, // read index
    output wire            o_idu_csr_ren,  
    output wire            o_idu_is_mret,
    output wire            o_idu_is_ecall,
    // to EXU
    output wire [1:0]      o_idu_csr_type,
    output wire [`ALU_Bus] o_idu_alu_type,
    output wire [1:0]      o_idu_num_sel,
    output wire [`CPU_Bus] o_idu_imm,
    // to to LSU
    output wire            o_idu_is_load,
    output wire            o_idu_is_store,
    output wire [2:0]      o_idu_func3,
    // to to to BRU
    output wire [`CPU_Bus] o_idu_pc,
    output wire            o_idu_is_jal,
    output wire            o_idu_is_jalr,
    output wire            o_idu_is_brch,
    // to to to WEU
    output wire [4:0]      o_idu_rd_id,
    output wire            o_idu_gpr_wen
);

    import "DPI-C" function void TRAP(input int station, input byte unit);

    //idu_reg_wen  = i_pre_valid & o_pre_ready
    //o_post_valid = i_pre_valid 延迟一周期
    //o_pre_ready  = ~o_post_valid
    // i_pre_valid --> ⌈‾‾‾‾‾⌉ --> o_post_valid
    //                 | IDU |
    // o_pre_ready <-- ⌊_____⌋ <-- i_post_ready



    /************ data package ************/
    // to Register File
    wire [4:0]      idu_rs_id1;
    wire [4:0]      idu_rs_id2;
    // to CSR Ctrl
    wire [`CSR_Bus] idu_csr_rid;  
    reg             idu_csr_ren;  // csr write and read enable
    reg             idu_is_mret;
    reg             idu_is_ecall;
    // to EXU
    reg  [1:0]      idu_csr_type;
    reg  [`ALU_Bus] idu_alu_type;
    reg  [1:0]      idu_num_sel;
    reg  [`CPU_Bus] idu_imm;
    // to to LSU
    wire            idu_is_load;
    wire            idu_is_store;
    wire [2:0]      idu_func3;
    // to to to BRU
    wire [`CPU_Bus] idu_pc;
    wire            idu_is_jal;
    wire            idu_is_jalr;
    wire            idu_is_brch;
    // to to to WEU
    wire [4:0]      idu_rd_id;
    reg             idu_gpr_wen;

    // decode
    wire [6:0] opcode = i_idu_inst[6:0];
    wire [4:0] rd_id  = i_idu_inst[11:7];
    wire [2:0] func3  = i_idu_inst[14:12];
    wire [4:0] rs_id1 = i_idu_inst[19:15];
    wire [4:0] rs_id2 = i_idu_inst[24:20];
    wire [6:0] func7  = i_idu_inst[31:25];


    // to CSR Ctrl
    assign idu_csr_rid  = {func7, rs_id2};
    always @(*) begin
        idu_csr_type = `CSR_RW;
        idu_csr_ren  = `Disen;
        idu_is_mret  = `FALSE;
        idu_is_ecall = `FALSE;
        case (opcode)
            `TYPE_SYS: begin 
                case (func3)
                    `INST_E_M: begin
                        if(idu_csr_rid == `INST_MRET)
                            idu_is_mret = `TRUE;
                        else if (idu_csr_rid == `INST_ECALL)
                            idu_is_ecall = `TRUE;
                        else if (idu_csr_rid == `INST_EBREAK)
                            TRAP(`HIT_TRAP, `Unit_IDU1);//uae
                        else
                            TRAP(`ABORT, `Unit_IDU2);  //uae
                    end
                    `INST_CSRRW: begin idu_csr_type = `CSR_RW; idu_csr_ren = `Enable; end
                    `INST_CSRRS: begin idu_csr_type = `CSR_RS; idu_csr_ren = `Enable; end
                    default: TRAP(`ABORT, `Unit_IDU3);  //uae
                endcase
            end
            `TYPE_R,`TYPE_I,`TYPE_I_LOAD,`TYPE_I_JALR,`TYPE_STORE,`TYPE_B,`TYPE_U_LUI,`TYPE_U_AUIPC,`TYPE_JAL:
                    idu_csr_type = `CSR_Nop;
            default:TRAP(`ABORT, `Unit_IDU4);  //uae
        endcase
    end


    // to EXU and WEU
    assign idu_rd_id = rd_id;
    always @(*) begin
        idu_num_sel = `RS1_RS2;  
        idu_gpr_wen = `Disen; 
        idu_imm     = `CPU_Width'd0;
        case (opcode)
            `TYPE_R:        begin idu_num_sel = `RS1_RS2;  idu_gpr_wen = `Enable;      idu_imm = `CPU_Width'd0;                                                              end
            `TYPE_I:        begin idu_num_sel = `RS1_IMM;  idu_gpr_wen = `Enable;      idu_imm = {{20{func7[6]}}, func7, rs_id2};                                            end
            `TYPE_I_LOAD:   begin idu_num_sel = `RS1_IMM;  idu_gpr_wen = `Enable;      idu_imm = {{20{func7[6]}}, func7, rs_id2};                                            end
            `TYPE_I_JALR:   begin idu_num_sel = `PC_4;     idu_gpr_wen = `Enable;      idu_imm = `CPU_Width'd0;                                                              end
            `TYPE_STORE:    begin idu_num_sel = `RS1_IMM;  idu_gpr_wen = `Disen;       idu_imm = {{20{func7[6]}}, func7, rd_id};                                             end
            `TYPE_B:        begin idu_num_sel = `RS1_RS2;  idu_gpr_wen = `Disen;       idu_imm = {{20{func7[6]}}, rd_id[0], func7[5:0], rd_id[4:1], 1'b0};                   end
            `TYPE_U_LUI:    begin idu_num_sel = `RS1_IMM;  idu_gpr_wen = `Enable;      idu_imm = {func7, rs_id2, rs_id1, func3, 12'd0};                                      end
            `TYPE_U_AUIPC:  begin idu_num_sel = `PC_IMM;   idu_gpr_wen = `Enable;      idu_imm = {func7, rs_id2, rs_id1, func3, 12'd0};                                      end
            `TYPE_JAL:      begin idu_num_sel = `PC_4;     idu_gpr_wen = `Enable;      idu_imm = {{12{func7[6]}}, rs_id1, func3, rs_id2[0], func7[5:0], rs_id2[4:1], 1'b0};  end                                 
            // idu_gpr_wen: when is INST_CSRRW or INST_CSRRS, idu_gpr_wen equalls to idu_csr_ren logically
            `TYPE_SYS:      begin idu_num_sel = `RS1_RS2;  idu_gpr_wen =  idu_csr_ren; idu_imm = `CPU_Width'd0;                                                              end
            default:        TRAP(`ABORT, `Unit_IDU5);  //uae
        endcase
    end

    always @(*) begin
        idu_alu_type = 0;
        case (opcode)
            `TYPE_I_LOAD,`TYPE_I_JALR,`TYPE_STORE,`TYPE_U_LUI,`TYPE_U_AUIPC,`TYPE_JAL:   
                                    idu_alu_type = `ALU_ADD;    
            `TYPE_R: begin
                case (func3)
                    `INST_ADD_SUB:  idu_alu_type = (func7[5] == 1'b0) ? `ALU_ADD : `ALU_SUB;
                    `INST_SLL:      idu_alu_type = `ALU_SLL;
                    `INST_SLT:      idu_alu_type = `ALU_LT;
                    `INST_SLTU:     idu_alu_type = `ALU_LTU;
                    `INST_XOR:      idu_alu_type = `ALU_XOR;
                    `INST_SRL_SRA:  idu_alu_type = (func7[5] == 1'b1) ? `ALU_SRA : `ALU_SRL;
                    `INST_OR:       idu_alu_type = `ALU_OR;
                    `INST_AND:      idu_alu_type = `ALU_AND;
                    default:        TRAP(`ABORT, `Unit_IDU6);  //uae
                endcase
            end
            `TYPE_I: begin
                case (func3)
                    `INST_ADDI:     idu_alu_type = `ALU_ADD;
                    `INST_SLLI:     idu_alu_type = `ALU_SLL;
                    `INST_SLTI:     idu_alu_type = `ALU_LT;
                    `INST_SLTIU:    idu_alu_type = `ALU_LTU;
                    `INST_XORI:     idu_alu_type = `ALU_XOR;
                    `INST_SRLAI:    idu_alu_type = (func7[5] == 1'b1) ? `ALU_SRA : `ALU_SRL;
                    `INST_ORI:      idu_alu_type = `ALU_OR;
                    `INST_ANDI:     idu_alu_type = `ALU_AND;
                    default:        TRAP(`ABORT, `Unit_IDU7);  //uae
                endcase
            end     
            `TYPE_B: begin
                case (func3)
                    `INST_BEQ:  idu_alu_type = `ALU_EQ;
                    `INST_BNE:  idu_alu_type = `ALU_NE;
                    `INST_BLT:  idu_alu_type = `ALU_LT;
                    `INST_BGE:  idu_alu_type = `ALU_GE;
                    `INST_BLTU: idu_alu_type = `ALU_LTU;
                    `INST_BGEU: idu_alu_type = `ALU_GEU;
                    default:    TRAP(`ABORT, `Unit_IDU8);  //uae
                endcase
            end                             
            default: if(opcode != `TYPE_SYS)  TRAP(`ABORT, `Unit_IDU9);  //uae
        endcase
    end
    // to Register File
    assign idu_rs_id1 = (idu_is_ecall == `TRUE) ? `MCASUSE_GPR :  // ecall: src1 = value of a17
                        (opcode == `TYPE_U_LUI) ? 5'd0 : rs_id1;  // lui : rd = x0 + imm
    assign idu_rs_id2 = rs_id2;
    // to to LSU
    assign idu_is_load  = (opcode == `TYPE_I_LOAD) ? `TRUE : `FALSE;
    assign idu_is_store = (opcode == `TYPE_STORE)  ? `TRUE : `FALSE;
    // to to BRU
    assign idu_pc      = i_idu_pc;
    assign idu_func3   = func3;
    assign idu_is_jal  = (opcode == `TYPE_JAL)    ? `TRUE : `FALSE;
    assign idu_is_jalr = (opcode == `TYPE_I_JALR) ? `TRUE : `FALSE;
    assign idu_is_brch = (opcode == `TYPE_B)      ? `TRUE : `FALSE;



    // data package
    wire idu_reg_wen  = i_pre_valid & o_pre_ready;   //数据包寄存器的写使能
    reg  [`IDU_PKG_WDITH-1 : 0] idu_valid_data_reg;  
    always @(posedge clk) begin
        if(rst == 1'b1) 
            idu_valid_data_reg <= 0;
        else if(idu_reg_wen == 1'b1)
            idu_valid_data_reg <= { idu_rs_id1, idu_rs_id2, idu_csr_rid, idu_csr_ren, idu_is_mret, 
                                    idu_is_ecall, idu_csr_type, idu_alu_type, idu_num_sel, idu_imm, 
                                    idu_is_load, idu_is_store, idu_func3, idu_pc, idu_is_jal, 
                                    idu_is_jalr, idu_is_brch, idu_rd_id, idu_gpr_wen };
    end

    assign {o_idu_rs_id1, o_idu_rs_id2, o_idu_csr_rid, o_idu_csr_ren, o_idu_is_mret, 
            o_idu_is_ecall, o_idu_csr_type, o_idu_alu_type, o_idu_num_sel, o_idu_imm, 
            o_idu_is_load, o_idu_is_store, o_idu_func3, o_idu_pc, o_idu_is_jal, 
            o_idu_is_jalr, o_idu_is_brch, o_idu_rd_id, o_idu_gpr_wen } = idu_valid_data_reg;



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

