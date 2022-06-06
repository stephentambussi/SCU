`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/01/2019 02:22:41 PM
// Design Name: 
// Module Name: tb_and
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

 // define testbench module
module tb_and();
    
// regs can store data
reg d1, d2; 

// can't store data, connects modules
wire out; 

// and_gate object
and_gate test(d1,d2,out);

// 'initial' means just to do it once (unlike 'always')
initial
begin
    // Out should be 0
    d1 = 0;
    d2 = 0; 
    
    #50; // wait 50 nanoseconds to see the change!
    
    // Out should be 0 
    d1 = 0; 
    d2 = 1;
    
    #50;
    
    // Out should be 0
    d1 = 1;
    d2 = 0;
    
    #50;

    // Out should be 1
    d1 = 1;
    d2 = 1;
    
    #50;

    $finish;
end
endmodule