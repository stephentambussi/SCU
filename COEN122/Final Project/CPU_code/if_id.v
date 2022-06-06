`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Instruction Fetch/Instruction Decode Buffer of CPU
//////////////////////////////////////////////////////////////////////////////////

module if_id(clk, pc_in, inst_in, pc_out, inst_out);
    //Inputs
    input clk;
    input [31:0] pc_in;
    input [31:0] inst_in;
    
    //Outputs
    output reg [31:0] pc_out;
    output reg [31:0] inst_out;
    
    always@(negedge clk)
    begin
        pc_out = pc_in;
        inst_out = inst_in;
    end

endmodule
