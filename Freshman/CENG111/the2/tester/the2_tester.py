from the2 import isCovered
import time
t1 = time.time()
number = 0
with open("the2_tester_data.txt","r") as file:
    data = file.read().split("\n")
    data[0] = data[0][1:]
    for ii in data:
        a = int(ii[3:5])
        b = int(ii[6:8])
        c = int(ii[11:13])
        d = int(ii[14:16])
        e = int(ii[19:21])
        f = int(ii[22:24])
        g = int(ii[27:29])
        h = int(ii[30:32])
        i = int(ii[35:37])
        j = int(ii[38:40])
        k = int(ii[43:45])
        l = int(ii[46:48])
        result = isCovered((a,b),(c,d),(e,f),(g,h),(i,j),(k,l))
        if result == ii[ii.find(":")+3:-2]:
            print("Succesful")
        elif   result != ii[ii.find(":")+3:-2]:
            print("Failed on {}".format(ii[:ii.find(":")]))
            print("Your work found: {}".format(result))
            print("It should have been {}.".format(ii[ii.find(":")+3:-2]))
            number += 1
    t2 = time.time()
    print("Execute time is: {}".format(t2-t1))
    print("In {} cases, you've failed {} times.".format(len(data),number))
    file.close