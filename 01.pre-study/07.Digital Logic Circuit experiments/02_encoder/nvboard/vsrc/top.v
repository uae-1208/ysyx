module top(
  input  wire [7:0] sw,
  input  wire       en,
  output reg  [2:0] led_rlt,
  output wire [7:0] hex0,
  output reg        led_indi  
);

  //led_rlt
  always @(*) begin
    if(en == 1'b0)
      led_rlt = 3'd0;
    else begin
      casez (sw)
        8'b1???_????: led_rlt = 3'd7; 
        8'b01??_????: led_rlt = 3'd6; 
        8'b001?_????: led_rlt = 3'd5; 
        8'b0001_????: led_rlt = 3'd4; 
        8'b0000_1???: led_rlt = 3'd3; 
        8'b0000_01??: led_rlt = 3'd2; 
        8'b0000_001?: led_rlt = 3'd1; 
        8'b0000_0001: led_rlt = 3'd0; 
        8'b0000_0000: led_rlt = 3'd0; 
        default: ;
      endcase
    end
  end

  //led_indi
  always@(*) begin
    if(en == 1'b0)
      led_indi = 1'b0;
    else if(sw == 8'b0000_0000)
      led_indi = 1'b0;
    else 
      led_indi = 1'b1;
  end
  
  //hex0
  bcd7seg seg(
    .b  ({1'b0, led_rlt}), 
    .h  (hex0));


endmodule
