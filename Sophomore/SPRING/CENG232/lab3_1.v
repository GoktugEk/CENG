// Code your design here


module kb(input K, input B, input clk, output reg Q);

  initial begin
		Q = 0;
	end

  always @ (posedge clk)
    begin
      if (~K & ~B)
        begin
          Q = ~Q;
        end
      else if (~K & B) 
        begin
          Q = 0;
        end
      else if (K & ~B) 
        begin
          Q = 1;
        end
      else
        begin
          Q = Q;
        end
    end
endmodule

module result1(input A0, input A1, input A2,input clk, output Q0, output Q1);
  kb kb0((A0 ~| A1) & ~A2,A1,clk,Q0);
  kb kb1(~A2,(~A0 | A1) ^ A2,clk,Q1);
endmodule

module ic232(input A0, input A1, input A2, input clk, output Q0, output Q1, output Z);

  result1 result10(A0,A1,A2,clk,Q0,Q1);
  assign Z = (Q0 ~^ Q1);


endmodule

