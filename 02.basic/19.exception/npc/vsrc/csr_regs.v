`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module csr_regs(
    input  wire           clk,
    input  wire           rst,
    input  wire           is_ecall,
    input  wire           csr_wen,
    input  wire [2:0]     funct3,
    input  wire [11:0]    csr,
    input  wire [`RegBus] src1,
    input  wire [`RegBus] pc,
    output wire [`RegBus] csr_npc,
    output reg  [`RegBus] csr_val
);

    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);

    reg [`RegBus] mstatus;
    reg [`RegBus] mtvec;
    reg [`RegBus] mepc;
    reg [`RegBus] mcause;
    wire[`RegBus] csr_wdata;


    // csr_wdata 
    // (funct3[1] == 1'b1) : csrrs
    // (funct3[1] == 1'b0) : csrrw or ecall
    assign csr_wdata = (funct3[1] == 1'b0) ? src1 : (src1 | csr_val);


    // {csr} = {funct7, rs2}
    // if csr[1] of mret is 1, npc = MEPC
    // while csr[1] of ecall is 0, npc = MTVEC
    assign csr_npc = (csr[1] == 1'b0) ? mtvec : mepc;


    // write register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
                mstatus <= `RegRstVal;  
                mtvec   <= `RegRstVal;  
                mepc    <= `RegRstVal;  
                mcause  <= `RegRstVal;  
        end else if(is_ecall == 1'b1) begin // The inst is 'ecall', and the src1 is gpr[15] (for riscv-32e)
            mepc   <= pc;
            mcause <= csr_wdata;
        end else if(csr_wen == 1'b1) begin
            case (csr)
                12'h300: mstatus <= csr_wdata;
                12'h305: mtvec   <= csr_wdata;
                12'h341: mepc    <= csr_wdata;
                12'h342: mcause  <= csr_wdata;
                default: ebreak(`ABORT, 32'hdead000a, `Unit_CR);  //uae
            endcase
        end 
    end


    //read register
    always @(*) begin
        case (csr)
            12'h300: csr_val = mstatus;
            12'h305: csr_val = mtvec;
            12'h341: csr_val = mepc;
            12'h342: csr_val = mcause;
            default: csr_val = 32'hdead000b;
        endcase
    end

endmodule
