`timescale 1ns / 1ps



module IntersectionSimulator(
	input [2:0] mode, //1xx:display, 000:remA, 001:remB, 010:addA, 011:addB
	input [4:0] plateIn,
	input action,
	input clk,
	output reg  greenForA,
	output reg  greenForB,
	output reg 	rushHourWarning,
	output reg [3:0]  hour,
	output reg [5:0]  minute,	
	output reg [5:0]  second,
	output reg	am_pm, //0:am, 1:pm
	output reg [4:0]  numOfCarsA,
	output reg [4:0]  numOfCarsB,
	output reg [6:0]  remainingTime,
	output reg [4:0]  blackListDisplay
	);
	
	//You may write your code anywhere
  
  	reg lightIndicator; //0 means A, 1 means B
    reg [7:0] minA;
    reg [7:0] maxA;
    reg [7:0] minB;
    reg [7:0] maxB;
    reg [7:0] lastTimeA;
    reg [7:0] lastTimeB;
    reg [7:0] nextTimeA;
    reg [7:0] nextTimeB;
    reg [4:0] carsOnA [0:30];
    reg [4:0] carsOnB [0:30];
    reg [4:0] blackList [0:30];
    reg [5:0] headA;
    reg [5:0] headB;
    reg [5:0] tailA;
    reg [5:0] tailB;
    reg [5:0] headBlack;
    reg [5:0] tailBlack;
    reg [5:0] numOfBlack;
  	integer i;
    reg [5:0] lastDisplayed;
  	reg [0:1] changeTime;
	
	initial begin
		greenForA=1;
		greenForB=0;
		rushHourWarning=0;
		hour=6;
		minute=0;
		second=0;
		am_pm=0;
		numOfCarsA=0;
		numOfCarsB=0;
		remainingTime=50;
		blackListDisplay=0;
        //...
      	maxB = 80;
      	minB = 50;
      	minA = 40;
      	maxA = 70;
      	lightIndicator = 0;
		lastTimeA = 40;
      	lastTimeB = 50;
      	nextTimeA = 40;
      	nextTimeB = 50;
		tailA = 0;
      	headA = 0;
      	tailB = 0;
      	headB = 0;
		headBlack = 0;
      	tailBlack = 0;
      	numOfBlack = 0;
      	lastDisplayed = 0;
      	changeTime = 0;
	end


	always@(posedge action)
	begin
      if (mode == 3'b000) begin
        //...
        lastDisplayed = 0;
        if(numOfCarsA == 0)
          numOfCarsA = 0;
         else begin
          if (greenForA == 0) begin
            blackList[tailBlack] = carsOnA[headA];
            tailBlack = tailBlack + 1;
            if(tailBlack == 30)
              tailBlack = 0;
            numOfBlack = numOfBlack +1;
          end
          headA = headA + 1;
          numOfCarsA = numOfCarsA -1;
          if (headA == 30)
            headA = 0;
         end
      end
      else if (mode == 3'b001) begin
        //...
        lastDisplayed = 0;
        if(numOfCarsB == 0)
          numOfCarsB = 0;
        else begin
          if (greenForB == 0) begin
            blackList[tailBlack] = carsOnB[headB];
            tailBlack = tailBlack + 1;
            if(tailBlack == 30)
              tailBlack = 0;
            numOfBlack = numOfBlack +1;
          end
          headB = headB + 1;
          numOfCarsB = numOfCarsB -1;
          if (headB == 30)
            headB = 0;
        end
      end
      else if (mode == 3'b010) begin
        //...
        lastDisplayed = 0;
        carsOnA[tailA] = plateIn;
        tailA = tailA + 1;
        numOfCarsA = numOfCarsA +1;
        if(tailA == 30)
          tailA = 0;
      end
      else if (mode == 3'b011) begin
        //...
        lastDisplayed = 0;
        carsOnB[tailB] = plateIn;
        tailB = tailB +1;
        numOfCarsB = numOfCarsB +1;
        if (tailB == 30)
          tailB = 0;
      end
		
		
		
	end


	always @(posedge clk)
	begin
      if(mode === 3'b1xx)begin
        //...
        if(numOfBlack == 0)
          blackListDisplay = 0;
        else if (lastDisplayed == numOfBlack)begin 
          lastDisplayed = 0;
        end
        blackListDisplay = blackList[(headBlack + lastDisplayed)%30];
        lastDisplayed = lastDisplayed + 1;
          
      end
      else if(mode == 3'b000 || mode == 3'b001 || mode == 3'b010 || mode == 3'b011 || mode === 3'b0xx) begin
        lastDisplayed =0;
        remainingTime = remainingTime -1;
		second = second + 1;
        if(changeTime == 1)
          changeTime = 2;
        
        if(second == 60) begin
          second = 0;
          minute = minute + 1;
        end
        if(minute >= 60) begin
          minute = minute % 60;
          hour = hour + 1;
        end
        if(hour == 12 && minute == 0 && second == 0) begin 
          if(am_pm == 0) 
            am_pm = 1;
          else
            am_pm = 0;
        end
        if(hour == 13)
          hour = 1;
        
        if (((hour >= 7 && hour < 9) && am_pm == 0) || ((hour >= 5 && hour < 7) && am_pm == 1)) 
          rushHourWarning = 1;
         else
           rushHourWarning = 0;
        
        if(rushHourWarning == 1) begin
          minA = 30;
          maxA = 60;
          minB = 40;
          maxB = 70;
        end
        else begin
          minB = 50;
          maxB = 80;
          minA = 40;
          maxA = 70;
        end
        
        if (remainingTime == 0) begin
          greenForA = 0;
          greenForB = 0;
          changeTime = 1;
        end

        if (changeTime == 2) begin
          changeTime = 0;
          if(lightIndicator == 0) begin
            //light will be green for B calculate the remaining time for B
            greenForB = 1;
            lightIndicator = 1;
            if(numOfCarsB >= 0 && numOfCarsB <= 10) begin
              nextTimeB = lastTimeB + 5;
              remainingTime = nextTimeA;
              lastTimeA = remainingTime;
            end
            else if(numOfCarsB >= 11 && numOfCarsB <= 19) begin
              remainingTime = nextTimeA;
              lastTimeA = remainingTime;
            end
            else if(numOfCarsB >= 20 && numOfCarsB <= 30) begin
              nextTimeB = lastTimeB -5;
              remainingTime = nextTimeA;
              lastTimeA = remainingTime;
            end
            if(nextTimeB > maxB)
              nextTimeB = maxB;
            else if(nextTimeB < minB)
              nextTimeB = minB;
          
          end
          else begin
            //light will be green for A calculate the remaining time A
            greenForA = 1;
            lightIndicator = 0;
            if(numOfCarsA >= 0 && numOfCarsA <= 10) begin
              nextTimeA = lastTimeA + 5;
              remainingTime = nextTimeB;
              lastTimeB = remainingTime;
            end
            else if(numOfCarsA >= 11 && numOfCarsA <= 19) begin
              remainingTime = nextTimeB;
              lastTimeB = remainingTime;
            end
            else if(numOfCarsA >= 20 && numOfCarsA <= 30) begin
              nextTimeA = lastTimeA - 5;
              remainingTime = nextTimeB;
              lastTimeB = remainingTime;
            end
            if(nextTimeA > maxA)
              nextTimeA = maxA;
            else if(nextTimeA < minA)
              nextTimeA = minA;
          end


        end
        
        
        if(hour == 12 && second == 0 && minute == 0 && am_pm == 0) begin
          for(i = 0; i<30; i = i+1) begin
            blackList[i] = 5'b00000;
          end
          headBlack = 0;
          tailBlack = 0;
          numOfBlack = 0;
        end
        
        
    end

      
		
	end


endmodule

