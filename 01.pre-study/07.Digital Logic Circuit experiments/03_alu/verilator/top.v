module top(
  input  wire [3:0] A,
  input  wire [3:0] b,
  input  wire [2:0] option,
  output reg        carry,
  output reg        overflow,
  output reg        zero,
  output reg  [3:0] result
);

  wire [3:0] a_s;
  wire       a_cin;
  reg  [3:0] B;
  //补码模块
  complement  complement_inst(
    .b      (b),
    .option (option),
    .B      (B));


  assign {a_cin, a_s} = A + B;

  //carry
  always @(*) begin
    case (option)
      3'b000: carry = a_cin;  //加法
      3'b001: carry = a_cin;  //减法
      3'b010: carry = 1'b0;   //取反
      3'b011: carry = 1'b0;   //与
      3'b100: carry = 1'b0;   //或
      3'b101: carry = 1'b0;   //异或
      3'b110: carry = a_cin;  //比较大小
      3'b111: carry = a_cin;  //判断相等
      default: ;
    endcase    
  end

  //overflow
  reg overflow_temp;
  assign overflow_temp = (A[3]==B[3]) && (A[3]!=a_s[3]);
  always @(*) begin
    case (option)
      3'b000: overflow = overflow_temp;  //带符号加法
      3'b001: overflow = overflow_temp;  //带符号减法
      3'b010: overflow = 1'b0;           //取反
      3'b011: overflow = 1'b0;           //与
      3'b100: overflow = 1'b0;           //或
      3'b101: overflow = 1'b0;           //异或
      3'b110: overflow = overflow_temp;  //带符号比较大小
      3'b111: overflow = overflow_temp;  //判断相等
      default: ;
    endcase    
  end

  assign zero = ~(|a_s);

  //result
  always @(*) begin
    case (option)
      3'b000: result = a_s;                              //加法
      3'b001: result = a_s;                              //减法
      3'b010: result = A ^ 4'hf;                         //取反
      3'b011: result = A & B;                            //与
      3'b100: result = A | B;                            //或
      3'b101: result = A ^ B;                            //异或
      3'b110: result = {3'd0, a_s[3] ^ overflow_temp};   //比较大小
      3'b111: result = {3'd0, {zero}};                   //判断相等
      default: ;
    endcase    
  end
endmodule





