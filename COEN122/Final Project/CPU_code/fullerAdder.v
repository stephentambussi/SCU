`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: PC Full Adder of CPU
//////////////////////////////////////////////////////////////////////////////////

module fullerAdder(A, clk, sum);
    input [31:0] A;
    input clk;
    output reg [31:0] sum;
    
    always@(posedge clk)
    begin
        sum = A + 1;
    end
endmodule
