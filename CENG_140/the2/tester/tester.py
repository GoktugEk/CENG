import os
import time

NUM_OF_TESTCASE = 6
wrong = 0
wrong_tcs = []
t1 = time.time()

for i in range(1,NUM_OF_TESTCASE+1):
	tc = "tc/testcase"+str(i)+".c"
	inp = "in/input"+str(i)+".txt"
	outp = "out/output"+str(i)+".txt"
	expe = "exp/expected"+str(i)+".txt"

	# os.system("gcc -c the2.c")
	# os.system("gcc -c " + tc)
	# os.system("gcc the2.o testcase"+str(i)+".o -o a")
	
	os.system("gcc -ansi -Wall -pedantic-errors the2.c tc/testcase"+str(i)+".c -lm -o a")

	os.system("./a <"+inp+" >"+outp)

	output = open(outp,"r+")
	out = output.read()

	expected = open(expe,"r+")
	exp = expected.read()

	if(exp != out):
		print( "Testcase"+str(i)+" Failed!\n")
		print("Correct Output:\n"+exp)
		print("\nYour Output:\n"+out)
		wrong_tcs.append("Testcase"+str(i))
		wrong+=1

print("You failed " + str(wrong) + " times on "+str(NUM_OF_TESTCASE)+" testcases.")
print("You failed on the cases: {}".format(wrong_tcs))
t2 = time.time()
print("Execute time is: {}".format(t2-t1))
