`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: 2-to-1 mux of CPU
//////////////////////////////////////////////////////////////////////////////////

module full_mux2to1(A, B, select, out);
    input [31:0] A;
    input [31:0] B;
    input select;
    
    output reg [31:0] out;
    
    always@(A,B,select)
    begin
        if(select == 0)
            out = A;
        if(select == 1)
            out = B;
    end
endmodule
