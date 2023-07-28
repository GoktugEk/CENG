`timescale 1ns / 1ps

module ROM (
input [2:0] addr, 
output reg [7:0] dataOut);
  
  always @(addr) begin
    if (addr[2] == 0 && addr[1] == 0 && addr[0] == 0)
      dataOut = {1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0};
    else if (addr[2] == 0 & addr[1] == 0 & addr[0] == 1)
      dataOut = {1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1};
    else if (addr[2] == 0 & addr[1] == 1 & addr[0] == 0)
      dataOut = {1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0};
    else if (addr[2] == 0 & addr[1] == 1 & addr[0] == 1)
      dataOut = {1'b0,1'b0,1'b1,1'b1,1'b0,1'b0,1'b1,1'b1};
    else if (addr[2] == 1 & addr[1] == 0 & addr[0] == 0)
      dataOut = {1'b1,1'b1,1'b0,1'b0,1'b1,1'b1,1'b0,1'b0};
    else if (addr[2] == 1 & addr[1] == 0 & addr[0] == 1)
      dataOut={1'b0,1'b0,1'b0,1'b0,1'b1,1'b1,1'b1,1'b1};
    else if (addr[0] == 1 & addr[1] == 1 & addr[0] == 0)
      dataOut = {1'b1,1'b1,1'b1,1'b1,1'b0,1'b0,1'b0,1'b0};
    else if (addr[2] == 1 & addr[1] == 1 & addr[0] == 1)
      dataOut = {1'b1,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1};
  end
	
endmodule




module XOR_RAM (
input mode, 
input [2:0] addr, 
input [7:0] dataIn, 
input [7:0] mask, 
input CLK, 
output reg [7:0] dataOut);
  
  reg [7:0]  mem [7:0];
  reg [7:0] temp;
  integer i,j,idx;
  integer th;
  
  
  
  initial begin
    for(i = 0; i<8 ; i = i+1) begin
      mem[i] = 8'b00000000;
    end
    assign dataOut = 8'b00000000;
    assign th = 1;

    
  end
  

  
  
  assign idx = addr[0] + addr[1]*2 + addr[2]*4;
  
  always@(*) begin
    if (idx>=0 && idx <=8)
      assign th = 0;
   end
  
  always@(mode,addr,dataIn,mask) begin
    if (th == 1)
      assign dataOut = 8'b00000000;
	else if (mode == 1) begin
      assign dataOut[0] = mem[idx][0];
      assign dataOut[1] = mem[idx][1];
      assign dataOut[2] = mem[idx][2];
      assign dataOut[3] = mem[idx][3];
      assign dataOut[4] = mem[idx][4];
      assign dataOut[5] = mem[idx][5];
      assign dataOut[6] = mem[idx][6];
      assign dataOut[7] = mem[idx][7];
    end
  end
  
  
  always@(posedge CLK) begin
    if (mode == 0) begin
      assign temp = dataIn ^ mask;

      mem[idx] = temp;

    end
  end
  

  
endmodule


module EncodedMemory (
input mode, 
input [2:0] index, 
input [7:0] number, 
input CLK, 
output [7:0] result);
	
	// DO NOT EDIT THIS MODULE
	
	wire [7:0] mask;
	
	ROM R(index, mask);
	XOR_RAM XR(mode, index, number, mask, CLK, result);

endmodule


