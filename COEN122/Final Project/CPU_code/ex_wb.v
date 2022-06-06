`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Execution/Write Back Buffer of CPU
//////////////////////////////////////////////////////////////////////////////////

module ex_wb(clk, rd, alu, data, regwrt, memtoreg, 
    rd_out, alu_out, data_out, regwrt_out, memtoreg_out);
    
    input clk, regwrt, memtoreg;
    input [31:0] alu;
    input [31:0] data;
    input [5:0] rd;
    
    output reg memtoreg_out, regwrt_out;
    output reg [31:0] alu_out;
    output reg [31:0] data_out;
    output reg [5:0] rd_out;
    
    always@(negedge clk) begin
        memtoreg_out = memtoreg;
        regwrt_out = regwrt;
        alu_out = alu;
        data_out = data;
        rd_out = rd;
    end
endmodule
