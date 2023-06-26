import os
import time

NUM_OF_TESTCASE = 10
wrong = 0
wrong_tcs = []
bar = NUM_OF_TESTCASE*10
t1 = time.time()

ops = ["solutions/Graph.cpp","solutions/HashUtils.cpp"]

print(bar * '.',end = '')
print("0%",end = '\r')

for compileFile in ops:
	os.system("g++ -c -Wall -pedantic-errors -O0 -std=c++11 " + compileFile)

for caseNum in range(1,NUM_OF_TESTCASE+1):
	os.system("g++ -c -Wall -pedantic-errors -O0 -std=c++11 tc/testcase" + str(caseNum) + ".cpp >> out/output" + str(caseNum)+".txt")


for caseNum in range(1,NUM_OF_TESTCASE+1):
	time.sleep(0.2)
	tc = "testcase"+str(caseNum)+".o"
	outp = "out/output"+str(caseNum)+".txt"
	expe = "exp/expected"+str(caseNum)+".txt"

	
	os.system("g++ -o a " + tc + " Graph.o HashUtils.o")

	os.system("./a  >"+outp)

	output = open(outp,"r+")
	out = output.read()

	expected = open(expe,"r+")
	exp = expected.read()

	if(exp != out):
		print( "Testcase"+str(caseNum)+" Failed!\n")
		print("Correct Output:\n"+exp)
		print("\nYour Output:\n"+out)
		wrong_tcs.append("Testcase"+str(caseNum))
		wrong+=1


	progress = int((caseNum/NUM_OF_TESTCASE)*bar)
	percantage = round((progress*100)/bar,1)
	print(progress*'#',end='')
	print((bar-progress)*'.',end = '')
	print(str(percantage)+ "%",end='\r')

os.system("rm *.o")
print("\nYou failed " + str(wrong) + " times on "+str(NUM_OF_TESTCASE)+" testcases.")
print("You failed on the cases: {}".format(wrong_tcs))
t2 = time.time()
t2 -= 3
print("Execute time is: {}".format(t2-t1))
