
module bcd7seg(
  input  wire [3:0] b,
  output reg  [7:0] h
);

    always @(*) begin
        case (b)
            4'd0:    h = 8'b00000011;
            4'd1:    h = 8'b10011111;
            4'd2:    h = 8'b00100101;
            4'd3:    h = 8'b00001101;
            4'd4:    h = 8'b10011001;
            4'd5:    h = 8'b01001001;
            4'd6:    h = 8'b01000001;
            4'd7:    h = 8'b00011111;
            4'd8:    h = 8'b00000001;
            4'd9:    h = 8'b00001001;
            default: h = 8'b11111111;
        endcase
    end

endmodule
