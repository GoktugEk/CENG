import sys
import os

def createExpecteds(filepath):
    ins = os.listdir("in/");
    for idx,f in enumerate(ins):
        print("./{} < in/" +  f + " > out/output"  + str(idx+1) + ".txt".format(filepath))
        os.system("./hw1 < in/" +  f + " > out/output"  + str(idx+1) + ".txt")
    


def main():
    ins = os.listdir("in/")


    for idx,f in enumerate(ins):

        print("./hw1 < in/" +  f + " > out/output"  + str(idx+1) + ".txt")
        os.system("./hw1 < in/" +  f + " > out/output"  + str(idx+1) + ".txt")
        
    createExpecteds("source")


    
    
       

    outs = os.listdir("out/")
    exps = os.listdir("exp/")


    createExpecteds()

    for out,exp in zip(outs,exps):
        pass
    
