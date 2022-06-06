`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Immediate Generator of CPU
//////////////////////////////////////////////////////////////////////////////////

module imm_gen(in, out, clk, inst);
    input clk;
    input [31:0] inst;
    input [21:0] in;
    output reg [31:0] out;
    wire [15:0] temp;
    assign temp = in[15:0];
    
    always@(in, out)
    begin
        if(inst[31:28] == 4'b1111 && inst[21] == 1) //Save PC, 1
            out = {10'b1111111111, in};
        else if(inst[31:28] == 4'b1111 && inst[21] == 0) //Save PC, 0
            out = {10'b0000000000, in};
        else if(inst[31:28] == 4'b0101 && inst[15] == 1) //Addi, 1
            out = {16'b1111111111111111, temp};
        else if(inst[31:28] == 4'b0101 && inst[15] == 0) //Addi, 0
            out = {16'b0000000000000000, temp};
    end
endmodule
