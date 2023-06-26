from the2 import isCovered
import time
import random
import json
# def myrand(s_range, e_range, other_num = -1):
    # num = random.randrange(s_range,e_range)
    # while num == other_num:
        # num = random.randrange(s_range,e_range)
    # return num

ii = 0
while ii < 235000:
    time1 = time.time()
    a = random.randrange(10,49)
    b = random.randrange(10, 49)
    c = random.randrange(a+1,51)
    d = random.randrange(b+1,51)
    e = random.randrange(10,99)
    f = random.randrange(10,99)
    g = random.randrange(e+1,100)
    h = random.randrange(f+1,100)
    i = random.randrange(10,99)
    j = random.randrange(10,99)
    k = random.randrange(i+1,100)
    l = random.randrange(j+1,100)

    res = {"({},{}),({},{}),({},{}),({},{}),({},{}),({},{})".format(a,b,c,d,e,f,g,h,i,j,k,l):isCovered((a,b),(c,d),(e,f),(g,h),(i,j),(k,l))}
    resj = json.dumps(res)
    with open("the2_tester_data.txt","a+", encoding = "utf-8") as file:
        file.writelines(resj)
        file.write("\n")
        file.close
    if ii%100 == 0:
        print(ii)
        time2= time.time()
        print(time2 - time1)
    ii += 1
    
    file.close