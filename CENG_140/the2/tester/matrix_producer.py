import random
import os


row = int(input(""))
size = int(input(""))


for i in range(row):
    for j in range(size):
        number = random.random()*6666
        print('%.4f' % number, end = '')
        print(' ',end = '')
    print("-1\n", end = '')
print("-1",end = '')


