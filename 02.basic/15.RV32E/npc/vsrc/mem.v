`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module mem(
    input  wire           valid,
    input  wire           wen_m,
    input  wire [7:0]     wmask,
    input  wire [`RegBus] waddr,
    input  wire [`RegBus] wdata,
    input  wire [`RegBus] raddr,
    output reg  [`RegBus] rdata
);
    wire         wen;
    assign wen = wen_m;


    import "DPI-C" function int  pmem_read(input int raddr);
    import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);


    // reg [31:0] rdata;
    always @(*) begin
        if(valid == 1'b1) begin // 有读写请求时
            rdata = pmem_read(raddr);
            if(wen) begin // 有写请求时
                // pmem_write(waddr, 32'hdeadbeaf, wmask);
                pmem_write(waddr, wdata, wmask);
            end
        end else begin
            rdata = 0;
        end
    end

endmodule
