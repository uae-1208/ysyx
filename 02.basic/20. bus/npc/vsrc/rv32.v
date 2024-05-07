`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module rv32(
  input  wire           clk,
  input  wire           rst
);

  reg [2:0] clk_cnt;
  always @(posedge clk) begin
    if(rst == 1'b1) 
      clk_cnt <= 3'h0;
    else if(clk_cnt == 3'h5)
      clk_cnt <= 3'h1;
    else
      clk_cnt <= clk_cnt + 3'h1;
  end


  // IFU --------------------------------------------------
  wire            w_ifu_valid;
  wire [`CPU_Bus] w_ifu_pc;
  wire [`CPU_Bus] w_ifu_inst;

  ifu ifu_inst(
    // system
    .clk         (clk),
    .rst         (rst),
    // shake hands
    .i_cycle_end (w_wbu_cycle_end),   
    .o_post_valid(w_ifu_valid),  
    .i_post_ready(w_idu_ready),  
    // from BRU
    .i_ifu_npc   (w_bru_npc),
    // to IDU
    .o_ifu_pc    (w_ifu_pc),
    .o_ifu_inst  (w_ifu_inst)
  );


  // IDU --------------------------------------------------
  wire            w_idu_ready;
  wire            w_idu_valid;
  wire [4:0]      w_idu_rs_id1;
  wire [4:0]      w_idu_rs_id2;
  wire [`CSR_Bus] w_idu_csr_rid;
  wire            w_idu_csr_ren;  
  wire            w_idu_is_mret;
  wire            w_idu_is_ecall;
  wire [1:0]      w_idu_csr_type;
  wire [`ALU_Bus] w_idu_alu_type;
  wire [1:0]      w_idu_num_sel;
  wire [`CPU_Bus] w_idu_imm;
  wire            w_idu_is_load;
  wire            w_idu_is_store;
  wire [2:0]      w_idu_func3;
  wire [`CPU_Bus] w_idu_pc;
  wire            w_idu_is_jal;
  wire            w_idu_is_jalr;
  wire            w_idu_is_brch;
  wire [4:0]      w_idu_rd_id;
  wire            w_idu_gpr_wen;

  idu idu_inst(
    // system
    .clk           (clk),
    .rst           (rst),
    // shake hands
    .i_pre_valid   (w_ifu_valid),   
    .o_pre_ready   (w_idu_ready), 
    .o_post_valid  (w_idu_valid),
    .i_post_ready  (w_exu_ready),
    // from IFU
    .i_idu_pc      (w_ifu_pc),
    .i_idu_inst    (w_ifu_inst),
    // to Register File
    .o_idu_rs_id1  (w_idu_rs_id1),
    .o_idu_rs_id2  (w_idu_rs_id2),
    // to CSR Ctrl
    .o_idu_csr_rid (w_idu_csr_rid),
    .o_idu_csr_ren (w_idu_csr_ren),  
    .o_idu_is_mret (w_idu_is_mret),
    .o_idu_is_ecall(w_idu_is_ecall),
    // to EXU
    .o_idu_csr_type(w_idu_csr_type),
    .o_idu_alu_type(w_idu_alu_type),
    .o_idu_num_sel (w_idu_num_sel),
    .o_idu_imm     (w_idu_imm),
    // to to LSU
    .o_idu_is_load (w_idu_is_load),
    .o_idu_is_store(w_idu_is_store),
    .o_idu_func3   (w_idu_func3),
    // to to to BRU
    .o_idu_pc      (w_idu_pc),
    .o_idu_is_jal  (w_idu_is_jal),
    .o_idu_is_jalr (w_idu_is_jalr),
    .o_idu_is_brch (w_idu_is_brch),
    // to to to WEU
    .o_idu_rd_id   (w_idu_rd_id),
    .o_idu_gpr_wen (w_idu_gpr_wen)
  );


  // EXU --------------------------------------------------
    wire            w_exu_ready;   
    wire            w_exu_valid;  
    wire [`CPU_Bus] w_exu_exu_res;
    wire            w_exu_is_load;
    wire            w_exu_is_store;
    wire [2:0]      w_exu_func3;
    wire [`CPU_Bus] w_exu_rs1;
    wire [`CPU_Bus] w_exu_rs2;
    wire [`CPU_Bus] w_exu_csr_npc;
    wire            w_exu_is_mret;
    wire            w_exu_is_ecall;
    wire [`CPU_Bus] w_exu_imm;
    wire [`CPU_Bus] w_exu_pc;
    wire            w_exu_is_jal;
    wire            w_exu_is_jalr;
    wire            w_exu_brch;
    wire [4:0]      w_exu_rd_id;
    wire            w_exu_gpr_wen;
    wire [`CSR_Bus] w_exu_csr_wid;
    wire [`RegBus]  w_exu_csr_rd;
    wire            w_exu_csr_wen;

  exu exu_inst(
    // system
    .clk           (clk),
    .rst           (rst),
    // shake hands
    .i_pre_valid   (w_idu_valid),   
    .o_pre_ready   (w_exu_ready),  
    .o_post_valid  (w_exu_valid),  
    .i_post_ready  (w_lsu_ready),  
    // from from IFU
    .i_exu_pc      (w_idu_pc),
    // from IDU
    .i_exu_alu_type(w_idu_alu_type),
    .i_exu_num_sel (w_idu_num_sel),
    .i_exu_imm     (w_idu_imm),
    .i_exu_is_jal  (w_idu_is_jal),
    .i_exu_is_jalr (w_idu_is_jalr),
    .i_exu_is_brch (w_idu_is_brch),
    .i_exu_is_load (w_idu_is_load),
    .i_exu_is_store(w_idu_is_store),
    .i_exu_func3   (w_idu_func3),
    .i_exu_rd_id   (w_idu_rd_id),
    .i_exu_gpr_wen (w_idu_gpr_wen),  
    .i_exu_csr_type(w_idu_csr_type),  
    .i_exu_csr_rid (w_idu_csr_rid),
    .i_exu_csr_ren (w_idu_csr_ren),  
    .i_exu_is_mret (w_idu_is_mret),
    .i_exu_is_ecall(w_idu_is_ecall),    
    // from Register File
    .i_exu_rs1     (w_rf_rs1),
    .i_exu_rs2     (w_rf_rs2),
    // from CSR Ctrl
    .i_exu_csr_src (w_cc_csr_src),
    .i_exu_csr_npc (w_cc_csr_npc),
    // to LSU
    .o_exu_exu_res (w_exu_exu_res),
    .o_exu_is_load (w_exu_is_load),
    .o_exu_is_store(w_exu_is_store),
    .o_exu_func3   (w_exu_func3),
    .o_exu_rs1     (w_exu_rs1),
    .o_exu_rs2     (w_exu_rs2),
    .o_exu_csr_npc (w_exu_csr_npc),
    .o_exu_is_mret (w_exu_is_mret),
    .o_exu_is_ecall(w_exu_is_ecall),
    // to to BRU
    .o_exu_imm     (w_exu_imm),
    .o_exu_pc      (w_exu_pc),
    .o_exu_is_jal  (w_exu_is_jal),
    .o_exu_is_jalr (w_exu_is_jalr),
    .o_exu_brch    (w_exu_brch),
    // to to WEU
    .o_exu_rd_id   (w_exu_rd_id),
    .o_exu_gpr_wen (w_exu_gpr_wen),
    .o_exu_csr_wid (w_exu_csr_wid),
    .o_exu_csr_rd  (w_exu_csr_rd),
    .o_exu_csr_wen (w_exu_csr_wen)
);


  // LSU --------------------------------------------------
  wire            w_lsu_ready;  
  wire            w_lsu_valid;  
  wire [`CPU_Bus] w_lsu_imm;
  wire [`CPU_Bus] w_lsu_pc;
  wire [`RegBus]  w_lsu_rs1;
  wire            w_lsu_is_jal;
  wire            w_lsu_is_jalr;
  wire            w_lsu_brch;    
  wire [`CPU_Bus] w_lsu_csr_npc;
  wire            w_lsu_is_ejump;
  wire [`CPU_Bus] w_lsu_rd;
  wire [4:0]      w_lsu_rd_id;
  wire            w_lsu_gpr_wen;
  wire            w_lsu_csr_wen;
  wire            w_lsu_is_mret;
  wire            w_lsu_is_ecall;
  wire [`CSR_Bus] w_lsu_csr_wid;
  wire [`RegBus]  w_lsu_csr_rd;

  lsu lsu_inst( 
    // system
    .clk           (clk),
    .rst           (rst),
    // shake hands
    .i_pre_valid   (w_exu_valid),  
    .o_pre_ready   (w_lsu_ready),  
    .o_post_valid  (w_lsu_valid),
    .i_post_ready  (w_wbu_ready),  
    // from from from IFU
    .i_lsu_pc      (w_exu_pc),
    // from from IDU
    .i_lsu_is_load (w_exu_is_load),
    .i_lsu_is_store(w_exu_is_store),
    .i_lsu_func3   (w_exu_func3),
    .i_lsu_imm     (w_exu_imm),
    .i_lsu_is_jal  (w_exu_is_jal),
    .i_lsu_is_jalr (w_exu_is_jalr),
    .i_lsu_brch    (w_exu_brch),
    .i_lsu_rd_id   (w_exu_rd_id),
    .i_lsu_gpr_wen (w_exu_gpr_wen),  
    // from from Register File
    .i_lsu_rs1     (w_exu_rs1),
    .i_lsu_rs2     (w_exu_rs2),
    // from from CSR Ctrl
    .i_lsu_csr_npc (w_exu_csr_npc),
    .i_lsu_csr_wid (w_exu_csr_wid),
    .i_lsu_csr_rd  (w_exu_csr_rd),
    .i_lsu_csr_wen (w_exu_csr_wen),  
    .i_lsu_is_mret (w_exu_is_mret),
    .i_lsu_is_ecall(w_exu_is_ecall),
    // from EXU
    .i_lsu_exu_res (w_exu_exu_res),
    // to BRU
    .o_lsu_imm     (w_lsu_imm),
    .o_lsu_pc      (w_lsu_pc),
    .o_lsu_rs1     (w_lsu_rs1),
    .o_lsu_is_jal  (w_lsu_is_jal),
    .o_lsu_is_jalr (w_lsu_is_jalr),
    .o_lsu_brch    (w_lsu_brch),    
    .o_lsu_csr_npc (w_lsu_csr_npc),
    .o_lsu_is_ejump(w_lsu_is_ejump),
    // to WEU
    .o_lsu_rd      (w_lsu_rd),
    .o_lsu_rd_id   (w_lsu_rd_id),
    .o_lsu_gpr_wen (w_lsu_gpr_wen),
    .o_lsu_csr_wen (w_lsu_csr_wen),
    .o_lsu_is_mret (w_lsu_is_mret),
    .o_lsu_is_ecall(w_lsu_is_ecall),
    .o_lsu_csr_wid (w_lsu_csr_wid),
    .o_lsu_csr_rd  (w_lsu_csr_rd)
  );


  // WBU --------------------------------------------------
  wire            w_wbu_ready; 
  wire            w_wbu_cycle_end;  
  wire            w_wbu_npc_wen;
  wire [`CPU_Bus] w_wbu_rd;
  wire [4:0]      w_wbu_rd_id;
  wire            w_wbu_gpr_wen;
  wire [`RegBus]  w_wbu_mcause_in;
  wire [`RegBus]  w_wbu_mepc_in;
  wire            w_wbu_csr_wen;  
  wire [`CSR_Bus] w_wbu_csr_wid;
  wire [`RegBus]  w_wbu_csr_rd;
    
  wbu wbu_inst(
    // system
    .clk           (clk),
    .rst           (rst),
    // shake hands
    .i_pre_valid   (w_lsu_valid),   
    .o_pre_ready   (w_wbu_ready),   
    .o_cycle_end   (w_wbu_cycle_end),   
    // from from from IFU
    .i_wbu_pc      (w_lsu_pc),
    // from from from IDU
    .i_wbu_rd_id   (w_lsu_rd_id),
    .i_wbu_gpr_wen (w_lsu_gpr_wen),  
    // from from from Register File
    .i_wbu_rs1     (w_lsu_rs1),
    // from from from CSR Ctrl
    .i_wbu_is_mret (w_lsu_is_mret),
    .i_wbu_is_ecall(w_lsu_is_ecall),
    .i_wbu_csr_wid (w_lsu_csr_wid),
    .i_wbu_csr_rd  (w_lsu_csr_rd),
    .i_wbu_csr_wen (w_lsu_csr_wen),
    // from LSU
    .i_wbu_rd      (w_lsu_rd),
    // to BRU
    .o_wbu_npc_wen (w_wbu_npc_wen),
    // to Register File
    .o_wbu_rd      (w_wbu_rd),
    .o_wbu_rd_id   (w_wbu_rd_id),
    .o_wbu_gpr_wen (w_wbu_gpr_wen),
    // to CSR Ctrl
    .o_wbu_mcause_in(w_wbu_mcause_in),
    .o_wbu_mepc_in  (w_wbu_mepc_in),
    .o_wbu_csr_wen  (w_wbu_csr_wen),  
    .o_wbu_csr_wid  (w_wbu_csr_wid),
    .o_wbu_csr_rd   (w_wbu_csr_rd)  
  );


  // BRU --------------------------------------------------
  wire [`CPU_Bus] w_bru_npc;
  
  bru bru_inst(
    // system
    .clk          (clk),
    .rst          (rst),
    // from from from from IFU
    .i_bru_pc     (w_lsu_pc),
    // from from from IFU
    .i_bru_imm    (w_lsu_imm),
    .i_bru_is_jal (w_lsu_is_jal),
    .i_bru_is_jalr(w_lsu_is_jalr),
    .i_bru_brch   (w_lsu_brch),
    .i_bru_ejump  (w_lsu_is_ejump),
    .i_bru_csr_npc(w_lsu_csr_npc),
    // from from from Register File
    .i_bru_rs1    (w_lsu_rs1),
    // from WBU
    .i_bru_npc_wen(w_wbu_npc_wen),
    // to IFU
    .o_bru_npc    (w_bru_npc)
  );


  // Register File --------------------------------------------------
  wire [`RegBus] w_rf_rs1;
  wire [`RegBus] w_rf_rs2;
  
  register_file  register_file_inst(
    // system
    .clk         (clk),
    .rst         (rst),
    // from WBU
    .i_rf_gpr_wen(w_wbu_gpr_wen),
    .i_rf_rd_id  (w_wbu_rd_id),
    .i_rf_rd     (w_wbu_rd),
    // from IDU
    .i_rf_rs_id1 (w_idu_rs_id1),
    .i_rf_rs_id2 (w_idu_rs_id2),
    // to EXU
    .o_rf_rs1    (w_rf_rs1),
    .o_rf_rs2    (w_rf_rs2)
  );


  // CSR Control --------------------------------------------------
    wire [`RegBus]  w_cc_csr_src;
    wire [`CPU_Bus] w_cc_csr_npc;
    
    csr_ctrl  csr_ctrl_inst(
    // system
    .clk            (clk),
    .rst            (rst),
    // from IDU
    .i_ccu_csr_ren  (w_idu_csr_ren),
    .i_ccu_csr_rid  (w_idu_csr_rid),
    .i_ccu_is_mret  (w_idu_is_mret),
    .i_ccu_is_ecall (w_idu_is_ecall),
    // from WBU
    .i_ccu_csr_wen  (w_wbu_csr_wen),
    .i_ccu_csr_wid  (w_wbu_csr_wid),
    .i_ccu_csr_rd   (w_wbu_csr_rd),
    .i_ccu_macuse_in(w_wbu_mcause_in),
    .i_ccu_mepc_in  (w_wbu_mepc_in),
    // to EXU
    .o_exu_csr_src  (w_cc_csr_src),
    .o_exu_csr_npc  (w_cc_csr_npc)
);

endmodule







// module PC(
//   input  wire           clk,
//   input  wire           rst,
//   input  wire           m1,
//   input  wire [1:0]     m2,
//   input  wire [`RegBus] result,
//   input  wire [`RegBus] imm32,
//   input  wire [`RegBus] csr_npc,
//   output wire [`RegBus] PCadd4,
//   output reg  [`RegBus] pc
// );

//   wire [`RegBus] npc;
//   wire [`RegBus] npc_temp;
//   wire [`RegBus] PCaddIMM32;
  
//   assign PCadd4     = pc + `PC_INCREMENT;
//   assign PCaddIMM32 = pc + imm32;

//   always @(posedge clk) begin
//     if(rst == `RST_VAL)
//       pc <= `RESET_VECTOR;
//     else if(clk == 1'b1)
//       pc <= npc;
//     else
//       pc <= pc;
//   end

//   // MUX1 module
//   MuxKey #(2, 1, `BitWidth) i1(npc, (m1 & result[0]), {
//       1'b0, npc_temp,
//       1'b1, PCaddIMM32}

//   );

//   // MUX2 module
//   MuxKey #(4, 2, `BitWidth) i2(npc_temp, (m2), {
//       `MUX2_PCadd4, PCadd4,
//       `MUX2_result, result,
//       `MUX2_CsrNpc, csr_npc,
//       `MUX2_IDLE,   32'hdead000c}       //uae
//   );

// endmodule





// module rv32(
//   input  wire           clk,
//   input  wire           rst
// );
  
//   wire[4:0]       rs1;
//   wire[4:0]       rs2;
//   wire[4:0]       rd;
//   wire[2:0]       funct3;
//   wire[6:0]       funct7;
// /* verilator lint_off UNOPTFLAT */
//   wire[`RegBus]   inst;     
// /* verilator lint_off UNOPTFLAT */
//   wire[`RegBus]   pc;     
//   wire[`TYPE_BUS] IType;      //inst type
//   wire            is_ecall;   //flag: if the current inst is 'ecall'
//   wire            csr_wen;    //csr write enable 
//   wire            reg_wen;    //RegFile write enable
//   wire            mem_wen;    //mem write enable
//   wire            mem_ren;    //mem read  enable
//   wire[7:0]       wmask;      //mem write mask
//   wire[2:0]       rmask;      //mem read  mask
//   wire            m1;         //mux1 sel
//   wire[1:0]       m2;         //mux2 sel
//   wire            m3;         //mux3 sel
//   wire            m4;         //mux4 sel
//   wire[1:0]       m5;         //mux5 sel
//   wire[`AlucBus]  aluc;       //alu operation type, like add, sub...
//   wire[`RegBus]   PCadd4;     //pc + 4
//   wire[`RegBus]   result;     //alu operation result
//   wire[`RegBus]   reg_in;     //regisrer file input value
//   wire[`RegBus]   src1;       //rs1 value
//   wire[`RegBus]   src2;       //rs2 value
//   wire[`RegBus]   imm32;      //extended 32 bit immediate
//   wire[`RegBus]   num1;       //alu operation number1       
//   wire[`RegBus]   num2;       //alu operation number2
//   wire[`RegBus]   mem_rdata;  //mem read data
//   wire[`RegBus]   csr_npc;    //next pc read from csr 
//   wire[`RegBus]   csr_val;    //csr value


//   // PC module
//   PC PC_inst(
//     .clk      (clk),
//     .rst      (rst),
//     .m1       (m1),
//     .m2       (m2),
//     .result   (result),
//     .imm32    (imm32),
//     .csr_npc  (csr_npc),
//     .PCadd4   (PCadd4),
//     .pc       (pc)   
//   );

//   // mem module
//   mem mem_inst(
//     .clk      (clk),  
//     .mem_wen  (mem_wen),  
//     .wmask    (wmask),
//     .waddr    (result),
//     .wdata    (src2),
//     .mem_ren  (mem_ren),  
//     .rmask    (rmask),
//     .raddr    (result),
//     .inst_addr(pc),
//     .rdata    (mem_rdata),
//     .inst_data(inst)
//   );

//   // Control Unit module
//   control_unit control_unit_inst(
//     .inst      (inst),
//     .rd_11_7   (rd),
//     .rs1_19_15 (rs1),
//     .rs2_24_20 (rs2),
//     .fun3_14_12(funct3),
//     .fun7_31_25(funct7),
//     .IType     (IType),
//     .aluc      (aluc),
//     .is_ecall  (is_ecall),    
//     .csr_wen   (csr_wen),    
//     .reg_wen   (reg_wen),    
//     .mem_wen   (mem_wen),
//     .mem_ren   (mem_ren),  
//     .wmask     (wmask),
//     .rmask     (rmask),
//     .m1        (m1),    
//     .m2        (m2),    
//     .m3        (m3),   
//     .m4        (m4),   
//     .m5        (m5)
//   );

//   // Register File module
//   register_file register_file_inst(
//     .clk      (clk),
//     .rst      (rst),
//     .is_ecall (is_ecall),
//     .reg_wen  (reg_wen),
//     .rs1      (rs1),
//     .rs2      (rs2),
//     .rd       (rd),
//     .reg_in   (reg_in),
//     .src1     (src1),
//     .src2     (src2)
//   );

//   // CSR Registers  module
//   csr_regs csr_regs_inst(
//     .clk     (clk),
//     .rst     (rst),
//     .is_ecall(is_ecall),
//     .csr_wen (csr_wen),
//     .funct3  (funct3),
//     .csr     ({funct7, rs2}),
//     .src1    (src1),
//     .pc      (pc),
//     .csr_npc (csr_npc),
//     .csr_val (csr_val)
//   );

//   // Imm Extend module
//   imm_extend imm_extend_inst(
//     .rs1   (rs1),
//     .rs2   (rs2),
//     .rd    (rd),
//     .funct3(funct3),
//     .funct7(funct7),
//     .IType (IType),
//     .imm32 (imm32)
//   );

//   // MUX3 module
//   MuxKey #(2, 1, `BitWidth) i3(num2, m3, {
//       `MUX3_src2,  src2,
//       `MUX3_imm32, imm32}
//   );

//   // MUX4 module
//   MuxKey #(2, 1, `BitWidth) i4(num1, m4, {
//       `MUX4_pc,   pc,
//       `MUX4_src1, src1}
//   );

//   // MUX5 module
//   MuxKey #(4, 2, `BitWidth) i5(reg_in, m5, {
//       `MUX5_PCadd4, PCadd4,
//       `MUX5_memdat, mem_rdata,
//       `MUX5_result, result,
//       `MUX5_CsrVal, csr_val} 
//   );
  
//   // ALU module
//   alu alu_inst(
//     .aluc  (aluc),
//     .num1  (num1),
//     .num2  (num2),
//     .result(result)
//   );
// endmodule


