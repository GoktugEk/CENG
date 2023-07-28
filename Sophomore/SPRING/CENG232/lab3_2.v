`timescale 1ns / 1ps
module QueueCounter(
  input [7:0] llmt,
  input [7:0] ulmt,
  input en,
  input mode, // 1:delete, 0:insert
  input clk,
  output reg [7:0] head,
  output reg [7:0] tail,
  output reg empty,
  output reg full);

  initial
    begin
      full = 0;
      empty = 1;
    end
  
  //you may write your code here

  initial
    begin
      head = llmt;
      tail = llmt;
    end

  //you may write your code here
  always @ (en | mode | clk)
    begin
      if(en & ~mode)
        begin
          if(~empty)
            begin
              if(head == ulmt)
                head = llmt;
              else
                head = head+1;
              if(full)
                full = 0;
            end
          if(head == tail)
            empty = 1;  
        end
      else if (en & mode)
        begin
          if(~full)
            begin
              if(tail == ulmt)
                tail = llmt;
              else
                tail = tail+1;
              if(empty)
                empty = 0;
            end
          if(head == tail)
            full = 1;
        end
    end




endmodule


module Numerator(
  input clinic, 
  input mode, 
  input en, 
  input clk,
  output [7:0] ann,
  output [7:0] print);

  //write your code here

  wire [7:0] a1;
  wire [7:0] p1;
  
  wire [7:0] a2;
  wire [7:0] p2;
  
  wire empty;
  wire full;
  
  
  QueueCounter q0(5,9,(~clinic) && en,mode,clk,a1,p1,empty,full);
  QueueCounter q1(10,14,clinic && en,mode,clk,a2,p2,empty,full);
  
  assign ann = (en) ? (~clinic ? a1 : a2) : ann ;
  assign print = (en) ? (~clinic  ? p1 : p2) : print ;
  

endmodule

