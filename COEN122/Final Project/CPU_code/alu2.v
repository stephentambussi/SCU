`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Better ALU of CPU
//////////////////////////////////////////////////////////////////////////////////

module alu2(A, B, Sel, Out, N, Z);
    input [31:0] A, B;
    input [2:0] Sel;
    output reg [31:0] Out;
    output reg N, Z;
    
    always@(A,B,Sel)
    begin
        if(Sel == 3'b100) //add
            Out = A + B;
        else if(Sel == 3'b010) //negate
            Out = ~B + 1;
        else if(Sel == 3'b001) //subtract
            Out = A + (~B + 1);
        else if(Sel == 3'b111) //pass value
            Out = A;
    end
    
    always@(Out)
    begin
        if(Sel != 3'b111)
        begin
            if(Out == 0)
                Z = 1;
            else if(Out != 0)
                Z = 0;
            if(Out[31] == 1)
                N = 1;
            else if(Out[31] == 0)
                N = 0;
        end
    end
        
endmodule
