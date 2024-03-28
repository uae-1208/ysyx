`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module clk_count(
  input  wire clk,
  input  wire rst,
  output wire clk0_flag,
  output wire clk1_flag,
  output wire clk2_flag
);

  reg [1:0] clk_cnt;
  always @(posedge clk) begin
    if(rst == `RST_VAL)
      clk_cnt <= 2'd0;
    else if(clk_cnt == 2'd2)
      clk_cnt <= 2'd0;
    else
      clk_cnt <= clk_cnt + 2'd1;
  end

  assign clk0_flag = (clk_cnt == 2'd0);
  assign clk1_flag = (clk_cnt == 2'd1);
  assign clk2_flag = (clk_cnt == 2'd2);

endmodule




module PC(
  input  wire           clk,
  input  wire           rst,
  input  wire           m3,
  input  wire           clk2_flag,
  input  wire [`RegBus] result,
  output wire [`RegBus] PCadd4,
  output reg  [`RegBus] pc
);

  reg [`RegBus] pc_temp;
  assign PCadd4 = pc + `PC_INCREMENT;

  always @(posedge clk) begin
    if(rst == `RST_VAL)
      pc <= `RESET_VECTOR;
    else if(clk2_flag == 1'b1)
      pc <= pc_temp;
  end

  // MUX3 module
  MuxKey #(2, 1, `BitWidth) i3(pc_temp, m3, {
      `MUX3_PCadd4, PCadd4,
      `MUX3_result, result}
  );

endmodule




module pc_reg(
  input  wire           clk,
  input  wire           rst,
  input  wire           clk0_flag,
  input  wire           clk2_flag,
  input  wire [`RegBus] mem_rdata,
  output reg  [`RegBus] inst
);

  reg  [`RegBus] inst_reg;

  always @(posedge clk) begin
    if(rst == `RST_VAL)
      inst_reg <= mem_rdata;
    else if(clk2_flag == 1'b1)
      inst_reg <= mem_rdata;
    else
      inst_reg <= inst;
  end

  always @(*) begin
    if(clk0_flag == 1'b1)
      inst = mem_rdata;
    else
      inst = inst_reg;
  end

endmodule





module rv32(
  input  wire           clk,
  input  wire           rst
);
  
  wire            clk0_flag;
  wire            clk1_flag;
  wire            clk2_flag;
  wire[4:0]       rs1;
  wire[4:0]       rs2;
  wire[4:0]       rd;
  wire[2:0]       funct3;
  wire[6:0]       funct7;
  /* verilator lint_off UNOPTFLAT */
  wire[`RegBus]   inst;     
  /* verilator lint_off UNOPTFLAT */
  wire[`RegBus]   pc;     
  wire[`TYPE_BUS] type4;      //inst type
  wire            wen_r;      //RegFile write enable
  wire            wen_m;      //mem write enable
  wire[7:0]       wmask;      //mem write mask
  wire            m1;         //mux1 sel
  wire            m2;         //mux2 sel
  wire            m3;         //mux3 sel
  wire[1:0]       m4;         //mux4 sel
  wire            m5;         //mux5 sel
  wire[`AlucBus]  aluc;       //alu operation type, like add, sub...
  wire[`RegBus]   PCadd4;     //pc + 4
  wire[`RegBus]   result;     //alu operation result
  wire[`RegBus]   rin;        //regisrer file input value
  wire[`RegBus]   src1;       //rs1 value
  wire[`RegBus]   src2;       //rs2 value
  wire[`RegBus]   imm;        //extended 32 bit immediate
  wire[`RegBus]   num1;       //alu operation number1       
  wire[`RegBus]   num2;       //alu operation number2
  wire[`RegBus]   raddr;      //mem read address
  wire[`RegBus]   mem_rdata;  //mem read data
  assign num1 = src1;


  // clk_count module
  clk_count clk_count_inst(
    .clk      (clk),
    .rst      (rst),
    .clk0_flag(clk0_flag),
    .clk1_flag(clk1_flag),
    .clk2_flag(clk2_flag)
  );

  // PC module
  PC PC_inst(
    .clk      (clk),
    .rst      (rst),
    .m3       (m3),
    .clk2_flag(clk2_flag),
    .result   (result),
    .PCadd4   (PCadd4),
    .pc       (pc)   
  );

  // pc_reg module
  pc_reg pc_reg_inst(
    .clk      (clk),
    .rst      (rst),
    .clk0_flag(clk0_flag),
    .clk2_flag(clk2_flag),
    .mem_rdata(mem_rdata),
    .inst     (inst)
  );

  // mem module
  mem mem_inst(
    .valid(1'b1),
    .wen_m(wen_m & clk1_flag & clk),  //uae:由于上下时钟沿都会更新电路状态，所以不加的 "& clk" 的话pmem_write会执行两次
    .wmask(wmask),
    .waddr(result),
    .wdata(src2),
    .raddr(raddr),
    .rdata(mem_rdata)
  );

  // Control Unit module
  control_unit control_unit_inst(
    .inst      (inst),
    .rd_11_7   (rd),
    .rs1_19_15 (rs1),
    .rs2_24_20 (rs2),
    .fun3_14_12(funct3),
    .fun7_31_25(funct7),
    .type1     (type4),
    .aluc      (aluc),
    .wen_r     (wen_r),    
    .wen_m     (wen_m),
    .wmask     (wmask),
    .m1        (m1),    
    .m2        (m2),    
    .m3        (m3),   
    .m4        (m4),   
    .m5        (m5) 
  );

  // Register File module
  register_file register_file_inst(
    .clk      (clk),
    .rst      (rst),
    .wen_r    (wen_r & clk1_flag),
    .rs1      (rs1),
    .rs2      (rs2),
    .rd       (rd),
    .rin      (rin),
    .src1     (src1),
    .src2     (src2)
  );

  // Imm Extend module
  imm_extend imm_extend_inst(
    .rs1   (rs1),
    .rs2   (rs2),
    .rd    (rd),
    .funct3(funct3),
    .funct7(funct7),
    .type3 (type4),
    .imm32 (imm)
  );

  // MUX1 module
  MuxKey #(2, 1, `BitWidth) i1(num1, m1, {
      `MUX1_pc,   pc,
      `MUX1_src1, src1}
  );

  // MUX2 module
  MuxKey #(2, 1, `BitWidth) i2(num2, m2, {
      `MUX2_src2, src2,
      `MUX2_imm,  imm}
  );

  // MUX4 module
  MuxKey #(4, 2, `BitWidth) i4(rin, m4, {
      `MUX4_PCadd4, PCadd4,
      `MUX4_result, result,
      `MUX4_memdat, mem_rdata,
      `MUX4_IDLE,   32'd0}       //uae
  );
  
  // MUX5 module
  MuxKey #(2, 1, `BitWidth) i5(raddr, (clk1_flag & m5), {
      1'b0, pc,
      1'b1, result}
  );

  // ALU module
  alu alu_inst(
    .aluc  (aluc),
    .num1  (num1),
    .num2  (num2),
    .result(result)
  );
endmodule


