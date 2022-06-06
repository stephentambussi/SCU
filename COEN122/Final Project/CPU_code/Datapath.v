`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Datapath Testbench of CPU
//////////////////////////////////////////////////////////////////////////////////

module Datapath();
    reg clk;
    
    //IF wires
    wire [31:0] pc_in, pc_out;
    wire [31:0] inst;
    wire [31:0] adder_out;
    
    //ID wires
    wire [31:0] pc_id;
    wire [31:0] inst_out;
    wire [31:0] rs1_out_id, rs2_out_id;
    wire [5:0] rd_id;
    wire [31:0] immgen_out;
    wire regwrt_id, memtoreg_id, pctoreg_id, brz_id, brn_id, jump_id, memread_id, memwrite_id, alusrc_id;
    wire [2:0] aluop_id;
    
    //EX wires
    wire regwrt_ex, memtoreg_ex, memread_ex, memwrite_ex, alusrc_ex, pctoreg_ex;
    wire [2:0] aluop_ex;
    wire [5:0] rd_ex;
    wire [31:0] rs1_ex, rs2_ex;
    wire [31:0] pc_ex;
    wire [31:0] immgen_ex;
    wire [31:0] mux1_out, mux2_out;
    wire Z_flag, N_flag;
    wire [31:0] datamem_out;
    wire [31:0] aluout;
    
    //WB wires
    wire [5:0] rd_wb;
    wire [31:0] datamem_wb;
    wire [31:0] aluout_wb;
    wire [31:0] mux_wb;
    wire regwrt_wb, memtoreg_wb;
    
    //Jump and Branch wires
    wire negativeAnd, zeroAnd, orOut;
    
    //IF components
    program_counter pc_reg(pc_in, pc_out, clk);
    instruction_mem instMem(clk, pc_out, inst);
    
    //IF/ID Buffer
    if_id IFID(clk, pc_out, inst, pc_id, inst_out);
    
    //ID components
    control ctrl(inst_out[31:28], aluop_id, memwrite_id, memread_id, alusrc_id, 
                regwrt_id, brz_id, brn_id, jump_id, memtoreg_id, pctoreg_id);
    register_file regFile(clk, regwrt_wb, rd_wb, inst_out[21:16], inst_out[15:10], mux_wb, rs1_out_id, rs2_out_id);
    imm_gen immGen(inst_out[21:0], immgen_out, clk, inst_out);
    
    assign rd_id = inst_out[27:22];
    
    //ID/EX Buffer
    id_ex IDEX(clk, rd_id, rs1_out_id, rs2_out_id, pc_id, immgen_out, memread_id, memtoreg_id, aluop_id, memwrite_id,
                alusrc_id, regwrt_id, pctoreg_id, rd_ex, rs1_ex, rs2_ex, pc_ex, immgen_ex, memread_ex, memtoreg_ex,
                aluop_ex, memwrite_ex, alusrc_ex, regwrt_ex, pctoreg_ex);
                
    //EX components
    data_mem dataMem(clk, memread_ex, memwrite_ex, rs1_ex, rs2_ex, datamem_out);
    full_mux2to1 mux1(rs1_ex, pc_ex, pctoreg_ex, mux1_out);
    full_mux2to1 mux2(rs2_ex, immgen_ex, alusrc_ex, mux2_out);
    alu2 ALU(mux1_out, mux2_out, aluop_ex, aluout, N_flag, Z_flag);
    
    //EX/WB Buffer
    ex_wb EXWB(clk, rd_ex, aluout, datamem_out, regwrt_ex, memtoreg_ex,
                rd_wb, aluout_wb, datamem_wb, regwrt_wb, memtoreg_wb);
    
    //WB components
    full_mux2to1 muxWB(aluout_wb, datamem_wb, memtoreg_wb, mux_wb);
    
    //Jump and Branch instructions
    and(negativeAnd, brn_id, N_flag);
    and(zeroAnd, brz_id, Z_flag);
    or(orOut, negativeAnd, zeroAnd, jump_id);
    
    //PC Input
    fullerAdder adder(pc_out, clk, adder_out);
    full_mux2to1 mux3(adder_out, rs1_out_id, orOut, pc_in);
    
    initial begin
        clk = 0;
        forever #5 clk =~ clk;
    end
    
    initial begin
        #1500
        $finish;
    end
    
endmodule
