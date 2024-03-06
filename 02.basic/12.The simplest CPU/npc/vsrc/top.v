`include "defines.v"

module PC(
  input  wire           clk,
  input  wire           rst,
  output reg  [`RegBus] pc
);

  reg [1:0] clk_div4;
  always @(posedge clk, posedge rst) begin
    if(rst == `RST_VAL)
      clk_div4 <= 2'd0;
    else if(clk_div4 == 2'd3)
      clk_div4 <= 2'd0;
    else
      clk_div4 <= clk_div4 + 2'd1;
  end


  always @(posedge clk, posedge rst) begin
    if(rst == `RST_VAL)
      pc <= `RESET_VECTOR;
    else if(clk_div4 == 2'd0)
      pc <= pc + `PC_INCREMENT;
  end

endmodule

//uae
//!!!!!!!!!!!!!!!!!!!!!
//测试一下rs1和rd相同的情况！！！！！
//!!!!!!!!!!!!!!!!!!!!!

module top(
  input  wire           clk,
  input  wire           rst,
  input  wire [`RegBus] inst,
  output wire [`RegBus] pc
);
  
  wire            rs1;
  wire            rs2;
  wire            rd;
  wire            funct7;
  wire[`TYPE_BUS] type;
  wire            m1;
  wire            aluc;
  wire[`RegBus]   result;
  wire[`RegBus]   src1;
  wire[`RegBus]   src2;
  wire[`RegBus]   imm;
  wire[`RegBus]   num1;
  wire[`RegBus]   num2;
  assign num1 = src1;


  // PC module
  PC PC_inst(
    .clk(clk),
    .rst(rst),
    .pc (pc)   
  );

  // Control Unit module
  control_unit control_unit_inst(
    .inst      (inst),
    .rd_11_7   (rd),
    .rs1_19_15 (rs1),
    .rs2_24_20 (rs2),
    .fun7_31_25(funct7),
    .type      (type),
    .aluc      (aluc),
    .m1        (m1)    
  );

  // Register File module
  register_file register_file_inst(
    .clk   (clk),
    .rst   (rst),
    .wen   (1'b1),   //uae
    .rs1   (rs1),
    .rs2   (rs2),
    .rd    (rd),
    .result(result),
    .src1  (src1),
    .src2  (src2)
  );

  // Imm Extend module
  imm_extend imm_extend_inst(
    .rs2   (rs2),
    .funct7(funct7),
    .type  (type),
    .imm32 (imm)
  );

  // MUX1 module
  MuxKey #(2, 1, 32) i1(num2, m1, {
      MUX1_src2, src2,
      MUX1_imm,  imm}
  );


  // ALU module
  alu alu_inst(
    .aluc  (aluc),
    .num1  (num1),
    .num2  (num2),
    .result(result)
  );
endmodule


