import random
import time


tree_length = int(input("Tree Length:"))

with open("input5.txt","w+") as file:
    file.write("{}\n".format(tree_length))
    for i in range(tree_length):
        file.write("{} {}\n".format(i,random.randrange(100)))


