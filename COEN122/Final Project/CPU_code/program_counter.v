`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Program counter of CPU
//////////////////////////////////////////////////////////////////////////////////

module program_counter(pc_in, pc_out, clk);
    input [31:0] pc_in;
    input clk;
    output reg [31:0] pc_out;
    
    initial 
    begin
        pc_out = 0;
    end
    
    always@(negedge clk)
    begin
        if(pc_in)
            pc_out = pc_in;
    end
endmodule
