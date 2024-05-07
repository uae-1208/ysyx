`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"
module csr_ctrl(
    // system
    input  wire            clk,
    input  wire            rst,
    // from IDU
    input  wire            i_ccu_csr_ren,
    input  wire [`CSR_Bus] i_ccu_csr_rid,
    input  wire            i_ccu_is_mret,
    input  wire            i_ccu_is_ecall,
    // from WBU
    input  wire            i_ccu_csr_wen,
    input  wire [`CSR_Bus] i_ccu_csr_wid,
    input  wire [`RegBus]  i_ccu_csr_rd,
    input  wire [`RegBus]  i_ccu_macuse_in,
    input  wire [`RegBus]  i_ccu_mepc_in,
    // to EXU
    output reg  [`RegBus]  o_exu_csr_src,
    output wire [`CPU_Bus] o_exu_csr_npc
);

    import "DPI-C" function void TRAP(input int station, input byte unit);

    reg [`RegBus] mstatus;
    reg [`RegBus] mtvec;
    reg [`RegBus] mepc;
    reg [`RegBus] mcause;


    // write register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            mstatus <= `RegRstVal;  
            mtvec   <= `RegRstVal;  
            mepc    <= `RegRstVal;  
            mcause  <= `RegRstVal;  
        end else if(i_ccu_is_ecall == `TRUE) begin
            mcause  <= i_ccu_macuse_in;
            mepc    <= i_ccu_mepc_in;
        end else if(i_ccu_csr_wen == `Enable) begin
            case (i_ccu_csr_wid)
                12'h300: mstatus <= i_ccu_csr_rd;
                12'h305: mtvec   <= i_ccu_csr_rd;
                12'h341: mepc    <= i_ccu_csr_rd;
                12'h342: mcause  <= i_ccu_csr_rd;
                default: TRAP(`ABORT, `Unit_CC1);  //uae
            endcase
        end 
    end

    //read register
    always @(*) begin
        if(i_ccu_csr_ren == `Enable)
            case (i_ccu_csr_rid)
                12'h300: o_exu_csr_src = mstatus;
                12'h305: o_exu_csr_src = mtvec;
                12'h341: o_exu_csr_src = mepc;
                12'h342: o_exu_csr_src = mcause;
                default: begin 
                    o_exu_csr_src = 32'hdead001c;
                    TRAP(`ABORT, `Unit_CC2);  //uae                
                end
            endcase
        else begin
                mstatus = mstatus;
                mtvec   = mtvec  ;
                mepc    = mepc   ;
                mcause  = mcause ;
        end
    end

    assign o_exu_csr_npc = (i_ccu_is_mret  == `TRUE) ? mepc  : 
                           (i_ccu_is_ecall == `TRUE) ? mtvec : 32'hdead005a;

endmodule
