
module bcd7seg(
  input  wire [3:0] b,
  output reg  [7:0] h
);

    always @(*) begin
        case (b)
            4'h0:    h = 8'b00000011;
            4'h1:    h = 8'b10011111;
            4'h2:    h = 8'b00100101;
            4'h3:    h = 8'b00001101;
            4'h4:    h = 8'b10011001;
            4'h5:    h = 8'b01001001;
            4'h6:    h = 8'b01000001;
            4'h7:    h = 8'b00011111;
            4'h8:    h = 8'b00000001;
            4'h9:    h = 8'b00001001;
            4'ha:    h = 8'b00010001;
            4'hb:    h = 8'b11000001;
            4'hc:    h = 8'b01100011;
            4'hd:    h = 8'b10000101;
            4'he:    h = 8'b01100001;
            4'hf:    h = 8'b01110001;
            default: h = 8'b11111111;
        endcase
    end

endmodule
