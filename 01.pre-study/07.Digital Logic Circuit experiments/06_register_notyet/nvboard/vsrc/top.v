module top(
  input  wire       clk,
  input  wire       rst,
  input  wire       ps2_clk,
  input  wire       ps2_data,
  output wire [7:0] hex0,
  output wire [7:0] hex1
);

  wire [7:0] data_temp;
  wire       ready_temp;
  
  ps2_keyboard ps2_keyboard_inst(
    .clk      (clk), 
    .rst      (rst), 
    .ps2_clk  (ps2_clk),
    .ps2_data (ps2_data),  
    .data     (data_temp),
    .ready    (ready_temp));  
    
  //hex0
  bcd7seg seg0(
    .b  (data_temp[3:0]), 
    .h  (hex0));
  //hex1
  bcd7seg seg1(
    .b  (data_temp[7:4]), 
    .h  (hex1));

endmodule
