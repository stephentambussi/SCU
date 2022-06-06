`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Instruction Memory of CPU
//////////////////////////////////////////////////////////////////////////////////

module instruction_mem(clk, address, instruction);
    input clk;
    input [31:0] address;
    
    output reg [31:0] instruction;
    wire [31:0] insts [255:0];
    
    //Instruction format
    //assign insts[x] = 32'b<opcode - 4bits>_<rd - 6bits>_<rs1 - 6bits>_<rs2 - 6bits>_<unused - 10bits>
    
    //Hard coded instructions for max program
    //This program finds the max from a set of numbers (numbers are hard coded in data_mem)
    assign insts[0] = 32'b00000000000000000000000000000000; //NOP
    assign insts[1] = 32'b00000000000000000000000000000000; //NOP
    assign insts[2] = 32'b00000000000000000000000000000000; //NOP
    assign insts[3] = 32'b00000000000000000000000000000000; //NOP
    assign insts[4] = 32'b00000000000000000000000000000000; //NOP
    assign insts[6] = 32'b0100_000101_000010_000011_0000000000; //ADD x5, x2, x3
    assign insts[7] = 32'b1111_001001_000000_000000_0000000010; //SVPC x9, 2 => rd = PC+Y
    assign insts[8] = 32'b1111_001010_000000_000000_0000001011; //SVPC x10, 11 => rd = PC+Y
    assign insts[9] = 32'b1110_000110_000010_000000_0000000000; //LD x6, x2
    assign insts[10] = 32'b00000000000000000000000000000000; //NOP
    assign insts[11] = 32'b00000000000000000000000000000000; //NOP
    assign insts[12] = 32'b00000000000000000000000000000000; //NOP
    assign insts[13] = 32'b0111_000111_000110_010100_0000000000; //SUB x7, x6, x20
    assign insts[14] = 32'b1011_000000_001010_000000_0000000000; //BRN x10
    assign insts[15] = 32'b00000000000000000000000000000000; //NOP
    assign insts[16] = 32'b00000000000000000000000000000000; //NOP
    assign insts[17] = 32'b00000000000000000000000000000000; //NOP
    assign insts[18] = 32'b0100_010100_000110_000000_0000000000; //ADD x20, x6, x0
    assign insts[19] = 32'b0101_000010_000010_000000_0000000001; //ADDi x2, x2, 1
    assign insts[20] = 32'b00000000000000000000000000000000; //NOP
    assign insts[21] = 32'b00000000000000000000000000000000; //NOP
    assign insts[22] = 32'b0111_001000_000010_000101_0000000000; //SUB x8, x2, x5
    assign insts[23] = 32'b1011_000000_001001_000000_0000000000; //BRN x9
    assign insts[24] = 32'b00000000000000000000000000000000; //NOP
    assign insts[25] = 32'b00000000000000000000000000000000; //NOP
    assign insts[26] = 32'b00000000000000000000000000000000; //NOP
    //Additional Instructions
    assign insts[27] = 32'b1010_000100_000000_000000_0000000000; //Where am I: WAI rd(x4)
    assign insts[28] = 32'b1000_000000_000001_000000_0000000000; //Jump: J rs1(x1) -- should call where am I again
    
    always@(posedge clk)
    begin
        instruction = insts[address];
    end
endmodule
