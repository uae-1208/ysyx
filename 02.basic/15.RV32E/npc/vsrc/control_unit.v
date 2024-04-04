`include "/home/uae/ysyx/ysyx-workbench/npc/vsrc/defines.v"

module control_unit(
    input  wire [`RegBus]   inst,
    output wire [4:0]       rd_11_7,
    output wire [4:0]       rs1_19_15,
    output wire [4:0]       rs2_24_20,
    output wire [2:0]       fun3_14_12,
    output wire [6:0]       fun7_31_25,
    output reg  [`TYPE_BUS] type1,      //inst type
    output reg  [`AlucBus]  aluc,       //alu operation typp
    output reg              wen_reg,    //RegFile write enable
    output reg              wen_mem,    //mem write enable
    output reg  [7:0]       wmask,      //mem write mask
    output reg  [2:0]       rmask,      //mem read  mask
    output reg              m1,         //mux1 sel
    output reg              m2,         //mux2 sel
    output reg              m3,         //mux3 sel
    output reg  [1:0]       m4,         //mux4 sel
    output reg              m5,         //mux5 sel
    output reg              m6          //mux6 sel
);

    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);

    wire [6:0] opcode_6_0 = inst[6:0];
    assign rd_11_7        = inst[11:7];
    assign rs1_19_15      = inst[19:15];
    assign rs2_24_20      = inst[24:20];
    assign fun3_14_12     = inst[14:12];  
    assign fun7_31_25     = inst[31:25];  

    always @(*) begin
        case(opcode_6_0)
            `INST_TYPE_R: begin
                type1   = `INST_R;   
                wen_reg = `WEnable;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                rmask   = `LoadW;   
                m1      = `MUX1_src1;
                m2      = `MUX2_src2;
                m3      = `MUX3_PCadd4;
                m4      = `MUX4_result;
                m5      = `MUX5_pc;
                m6      = `MUX6_PCadd4;
                if(fun7_31_25 == 7'b000_0000) begin
                    case (fun3_14_12)
                        `INST_ADD:  aluc = `ADD;
                        `INST_SLL:  aluc = `SLL;
                        `INST_SLTU: aluc = `SLTU;
                        `INST_XOR:  aluc = `XOR;
                        `INST_SRL:  aluc = `SRL;
                        `INST_OR:   aluc = `OR;
                        `INST_AND:  aluc = `AND;
                        default:    ebreak(`ABORT, inst, `Unit_CU1); //uae
                    endcase                
                end else if(fun7_31_25 == 7'b010_0000) begin
                    case (fun3_14_12)
                        `INST_SUB: aluc = `SUB;
                        `INST_SRA: aluc = `SRA;
                        default:   ebreak(`ABORT, inst, `Unit_CU2); //uae
                    endcase  
                end else begin
                    ebreak(`ABORT, inst, `Unit_CU3);  //uae
                end
            end
            `INST_TYPE_I: begin
                type1   = `INST_I;   
                wen_reg = `WEnable;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                rmask   = `LoadW;   
                m1      = `MUX1_src1;
                m2      = `MUX2_imm;
                m3      = `MUX3_PCadd4;
                m4      = `MUX4_result;
                m5      = `MUX5_pc;
                m6      = `MUX6_PCadd4;
                case (fun3_14_12)
                    `INST_ADDI:  aluc = `ADD;
                    `INST_SLTIU: aluc = `SLTU;
                    `INST_XORI:  aluc = `XOR;
                    `INST_ANDI:  aluc = `AND;
                    `INST_SLLI:  aluc = `SLL;
                    `INST_SRLAI:begin 
                                    case (fun7_31_25)
                                        7'b000_0000: aluc = `SRL;
                                        7'b010_0000: aluc = `SRA;
                                        default: ebreak(`ABORT, inst, `Unit_CU4);  //uae
                                    endcase
                                end 
                     default:     ebreak(`ABORT, inst, `Unit_CU5);  //uae
                endcase
            end          
            `INST_TYPE_L: begin
                type1   = `INST_I; 
                aluc    = `ADD;  
                wen_reg = `WEnable;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                m1      = `MUX1_src1;
                m2      = `MUX2_imm;
                m3      = `MUX3_PCadd4;
                m4      = `MUX4_memdat;
                m5      = `MUX5_result;
                m6      = `MUX6_PCadd4;
                case (fun3_14_12)
                    `INST_LH:  rmask = `LoadH;
                    `INST_LW:  rmask = `LoadW;
                    `INST_LBU: rmask = `LoadBU;
                    `INST_LHU: rmask = `LoadHU;
                    default:  ebreak(`ABORT, inst, `Unit_CU6);  //uae
                endcase
            end
            `INST_TYPE_S: begin
                type1   = `INST_S;   
                aluc    = `ADD;
                wen_reg = `WDisen;   
                wen_mem = `WEnable;   
                rmask   = `LoadW;   
                m1      = `MUX1_src1;
                m2      = `MUX2_imm;
                m3      = `MUX3_PCadd4;
                m4      = `MUX4_result;
                m5      = `MUX5_pc;
                m6      = `MUX6_PCadd4;
                case (fun3_14_12)
                    `INST_SB: wmask = `WByte;
                    `INST_SH: wmask = `WHalf;
                    `INST_SW: wmask = `WWord;
                    default:  ebreak(`ABORT, inst, `Unit_CU7);  //uae
                endcase
            end
            `INST_TYPE_B: begin
                type1   = `INST_B;   
                wen_reg = `WDisen;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                rmask   = `LoadW;   
                m1      = `MUX1_src1;
                m2      = `MUX2_src2;
                m3      = `MUX3_PCadd4;
                m4      = `MUX4_result;
                m5      = `MUX5_pc;
                m6      = `MUX6_bump;
                case (fun3_14_12)
                    `INST_BEQ:  aluc = `BEQ;
                    `INST_BNE:  aluc = `BNE;
                    `INST_BLT:  aluc = `BLT;
                    `INST_BGE:  aluc = `BGE;
                    `INST_BLTU: aluc = `BLTU;
                    `INST_BGEU: aluc = `BGEU;
                    default:   ebreak(`ABORT, inst, `Unit_CU8);  //uae
                endcase
            end
            `INST_TYPE_LUI: begin
                type1   = `INST_U;   
                wen_reg = `WEnable;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                rmask   = `LoadW;   
                m1      = `MUX1_pc;
                m2      = `MUX2_imm;
                m3      = `MUX3_PCadd4;
                m4      = `MUX4_result;
                m5      = `MUX5_pc;
                m6      = `MUX6_PCadd4;
                aluc    = `ADD_LUI;
            end
            `INST_TYPE_AUIPC: begin
                type1   = `INST_U;   
                wen_reg = `WEnable;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                rmask   = `LoadW;   
                m1      = `MUX1_pc;
                m2      = `MUX2_imm;
                m3      = `MUX3_PCadd4;
                m4      = `MUX4_result;
                m5      = `MUX5_pc;
                m6      = `MUX6_PCadd4;
                aluc    = `ADD;
            end
            `INST_TYPE_JALR: begin
                type1   = `INST_I;   
                wen_reg = `WEnable;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                rmask   = `LoadW;   
                m1      = `MUX1_src1;
                m2      = `MUX2_imm;
                m3      = `MUX3_result;
                m4      = `MUX4_PCadd4;
                m5      = `MUX5_pc;
                m6      = `MUX6_PCadd4;
                aluc    = `ADD_JALR;
            end            
            `INST_TYPE_JAL: begin
                type1   = `INST_J;   
                wen_reg = `WEnable;   
                wen_mem = `WDisen;   
                wmask   = `WWord;   
                rmask   = `LoadW;   
                m1      = `MUX1_pc;
                m2      = `MUX2_imm;
                m3      = `MUX3_result;
                m4      = `MUX4_PCadd4;
                m5      = `MUX5_pc;
                m6      = `MUX6_PCadd4;
                aluc    = `ADD;
            end
            `INST_TYPE_E: begin
                case ({fun7_31_25, rs2_24_20})
                    `INST_EBREAK: ebreak(`HIT_TRAP, inst, `Unit_CU9);
                     default:     ebreak(`ABORT, inst, `Unit_CU10);
                endcase
            end
            default: begin   //uae
                ebreak(`ABORT, inst, `Unit_CU11);
                // type1 = 3'd0;
                // m1    = `MUX1_src1;
                // m2    = `MUX2_imm;
                // m3    = `MUX3_PCadd4;
                // aluc  = `ADD;
            end
        endcase
    end

endmodule
