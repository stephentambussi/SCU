`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//  Name: Stephen Tambussi & Kevin Molumphy
//  Date: 6/3/2022
//  Topic: COEN122 - Final Project
//  Description: Data Memory of CPU
//////////////////////////////////////////////////////////////////////////////////

module data_mem(clk, read, write, address, datain, dataout);
    input clk, read, write;
    input [31:0] address;
    input [31:0] datain;
    
    output reg [31:0] dataout;
    
    reg [31:0] data[65535:0];
    
    /*
    reg [31:0] n;
    
    initial begin
        $readmemb("numbers_max.mem", data, 0);
            for(n=2; n<7; n=n+1)
            $display("[$DISPLAY1 time=%t data at memory location %d = %b", $time, n, data[n]);
    end
    */
    
    initial begin
        //numbers of array to find max
        data[2] = 3;
        data[3] = -4;
        data[4] = 5;
        data[5] = 2;
        data[6] = 20;
    end
    
    always@(posedge clk)
    begin
        if(read == 1)
            dataout = data[address[15:0]];
        else if(write == 1)
            data[address[15:0]] = datain;
    end
endmodule
