`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module clk_count(
  input  wire clk,
  input  wire rst,
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

  assign clk1_flag = (clk_cnt == 2'd1);
  assign clk2_flag = (clk_cnt == 2'd2);

endmodule



module PC(
  input  wire           clk,
  input  wire           rst,
  input  wire           clk2_flag,
  output reg  [`RegBus] pc
);

  always @(posedge clk) begin
    if(rst == `RST_VAL)
      pc <= `RESET_VECTOR;
    else if(clk2_flag == 1'b1)
      pc <= pc + `PC_INCREMENT;
  end

endmodule



module rv32(
  input  wire           clk,
  input  wire           rst,
  input  wire [`RegBus] inst,
  output wire [`RegBus] pc
);
  
  wire            clk1_flag;
  wire            clk2_flag;
  wire [4:0]      rs1;
  wire [4:0]      rs2;
  wire [4:0]      rd;
  wire [6:0]      funct7;
  wire[`TYPE_BUS] type4;      //inst type
  wire            m1;         //mux1 sel
  wire[`AlucBus]  aluc;       //alu operation type, like add, sub...
  wire[`RegBus]   result;     //alu operation result
  wire[`RegBus]   src1;       //rs1 value
  wire[`RegBus]   src2;       //rs2 value
  wire[`RegBus]   imm;        //extended 32 bit immediate
  wire[`RegBus]   num1;       //alu operation number1       
  wire[`RegBus]   num2;       //alu operation number2
  assign num1 = src1;


  // clk_count module
  clk_count clk_count_inst(
    .clk      (clk),
    .rst      (rst),
    .clk1_flag(clk1_flag),
    .clk2_flag(clk2_flag)
  );

  // PC module
  PC PC_inst(
    .clk      (clk),
    .rst      (rst),
    .clk2_flag(clk2_flag),
    .pc       (pc)   
  );

  // Control Unit module
  control_unit control_unit_inst(
    .inst      (inst),
    .rd_11_7   (rd),
    .rs1_19_15 (rs1),
    .rs2_24_20 (rs2),
    .fun7_31_25(funct7),
    .type1     (type4),
    .aluc      (aluc),
    .m1        (m1)    
  );

  // Register File module
  register_file register_file_inst(
    .clk      (clk),
    .rst      (rst),
    .clk1_flag(clk1_flag),
    .rs1      (rs1),
    .rs2      (rs2),
    .rd       (rd),
    .result   (result),
    .src1     (src1),
    .src2     (src2)
  );

  // Imm Extend module
  imm_extend imm_extend_inst(
    .rs2   (rs2),
    .funct7(funct7),
    .type3 (type4),
    .imm32 (imm)
  );

  // MUX1 module
  MuxKey #(2, 1, 32) i1(num2, m1, {
      `MUX1_src2, src2,
      `MUX1_imm,  imm}
  );


  // ALU module
  alu alu_inst(
    .aluc  (aluc),
    .num1  (num1),
    .num2  (num2),
    .result(result)
  );
endmodule


