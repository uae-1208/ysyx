module ps2_keyboard(
  input  wire       clk,
  input  wire       rst,
  input  wire       ps2_clk,
  input  wire       ps2_data,
  output reg  [7:0] data,
  output reg        ready
  
);

  reg [9:0] buffer;    // ps2_data bits
  reg [3:0] count;     // count ps2_data bits
  reg [2:0] ps2_clk_sync;

  always @(posedge clk) begin
      ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
  end

  wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

  always @(posedge clk) begin
      if(rst == 1'b1)  // reset
          count <= 0;
      else begin
        ready <= 1'b0;
        if (sampling) begin
          if (count == 4'd10) begin
            if ((buffer[0] == 0) &&  // start bit
                (ps2_data)       &&  // stop bit
                (^buffer[9:1])) begin      // odd  parity
                data <= buffer[8:1];
                ready <= 1'b1;
            end
            count <= 0;     // for next
          end 
          else begin
            buffer[count] <= ps2_data;  // store ps2_data
            count <= count + 3'b1;
          end
        end
      end
  end

endmodule