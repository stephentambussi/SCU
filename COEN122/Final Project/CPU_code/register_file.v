`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Register File of CPU
//////////////////////////////////////////////////////////////////////////////////

module register_file(clk, wrt, rd, rs1, rs2, datain, rs1out, rs2out);
    input clk, wrt;
    input [5:0] rd; //64 possible values with 6-bit address
    input [5:0] rs1;
    input [5:0] rs2;
    input [31:0] datain;
    //2D array - register memory holds 64 32-bit values
    reg [31:0] registers [63:0];
    
    output reg [31:0] rs1out;
    output reg [31:0] rs2out;
    
    initial begin
        //assumptions of array
        registers[0] = 0;
        registers[1] = 27; //for the jump instruction
        registers[2] = 2; //base address of array
        registers[3] = 5; //n-1
        registers[20] = 1; //initialize x20
    end
    
    always@(negedge clk) //write on negedge if write == 1
    begin
        if(wrt == 1)
            registers[rd] = datain;
    end
    
    always@(rs1, rs2) //read on posedge
    begin
        rs1out = registers[rs1];
        rs2out = registers[rs2];
    end
    
endmodule
