module complement(
  input  wire [3:0] b,
  input  wire [2:0] option,
  output reg  [3:0] B
);
    //b的补码
    reg [3:0] temp = ~b + 4'h1;

    always @(*) begin
        case (option)
            3'b000: B = b;      //加法
            3'b001: B = temp;   //减法
            3'b010: B = b;      //取反
            3'b011: B = b;      //与
            3'b100: B = b;      //或
            3'b101: B = b;      //异或
            3'b110: B = temp;   //比较大小
            3'b111: B = temp;   //判断相等
            default: ;
        endcase
    end
endmodule