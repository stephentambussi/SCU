`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Control of CPU
//////////////////////////////////////////////////////////////////////////////////

module control(opcode, alu_op, memwrite, memread, alu_src, regwrt, brz, brn, jump, memtoreg, pctoreg);
    input [3:0] opcode;
    output reg memwrite, memread, alu_src, regwrt, brz, brn, jump, memtoreg, pctoreg;
    output reg [2:0] alu_op;
    
    always@(opcode)
    begin
        case(opcode)
            4'b0000: //NOP
            begin
                alu_op = 0;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 0;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b1111: //Save PC
            begin
                alu_op = 3'b100;
                memwrite = 0;
                memread = 0;
                alu_src = 1;
                regwrt = 1;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 1;
            end
            4'b1110: //Load
            begin
                alu_op = 3'b111;
                memwrite = 0;
                memread = 1;
                alu_src = 0;
                regwrt = 1;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 1;
                pctoreg = 0;
            end
            4'b0011: //Store
            begin
                alu_op = 3'b111;
                memwrite = 1;
                memread = 0;
                alu_src = 0;
                regwrt = 0;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b0100: //Add
            begin
                alu_op = 3'b100;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 1;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b0101: //Add Immediate
            begin
                alu_op = 3'b100;
                memwrite = 0;
                memread = 0;
                alu_src = 1;
                regwrt = 1;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b0110: //Negate
            begin
                alu_op = 3'b010;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 1;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b0111: //Subtract
            begin
                alu_op = 3'b001;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 1;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b1000: //Jump
            begin
                alu_op = 3'b111;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 0;
                brz = 0;
                brn = 0;
                jump = 1;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b1001: //Branch if zero
            begin
                alu_op = 3'b111;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 0;
                brz = 1;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
            4'b1010: //Where am I
            begin
                alu_op = 3'b111;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 1;
                brz = 0;
                brn = 0;
                jump = 0;
                memtoreg = 0;
                pctoreg = 1;
            end
            4'b1011: //Branch if negative
            begin
                alu_op = 3'b111;
                memwrite = 0;
                memread = 0;
                alu_src = 0;
                regwrt = 0;
                brz = 0;
                brn = 1;
                jump = 0;
                memtoreg = 0;
                pctoreg = 0;
            end
        endcase
    end
endmodule
