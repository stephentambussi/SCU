`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Instruction Decode/Execution Buffer of CPU
//////////////////////////////////////////////////////////////////////////////////

module id_ex(clk, rd, rs1, rs2, pc, immgen, memread, memtoreg, aluop, memwrite, alusrc, regwrt, pctoreg,
    rd_out, rs1_out, rs2_out, pc_out, immgen_out, memread_out, memtoreg_out, aluop_out, memwrite_out, alusrc_out,
    regwrt_out, pctoreg_out);
    
    input [31:0] immgen;
    input [5:0] rd;
    input [31:0] rs1;
    input [31:0] rs2;
    input [31:0] pc;
    input clk, memread, memtoreg, memwrite, alusrc, regwrt, pctoreg;
    input [2:0] aluop;
    
    output reg memread_out, memtoreg_out, memwrite_out, alusrc_out, regwrt_out, pctoreg_out;
    output reg [2:0] aluop_out;
    output reg [5:0] rd_out;
    output reg [31:0] rs1_out;
    output reg [31:0] rs2_out;
    output reg [31:0] pc_out;
    output reg [31:0] immgen_out;
    
    always@(negedge clk) begin
        memread_out = memread;
        memtoreg_out = memtoreg;
        aluop_out = aluop;
        memwrite_out = memwrite;
        alusrc_out = alusrc;
        regwrt_out = regwrt;
        pctoreg_out = pctoreg;
        rd_out = rd;
        rs1_out = rs1;
        rs2_out = rs2;
        pc_out = pc;
        immgen_out = immgen;
    end
endmodule
