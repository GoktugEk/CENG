import random
import the4_original
import time
t1 = time.time()
with open("the4_data.json","a+") as file:
    for i in range(1000):
        a = random.randrange(1,11)
        b = random.randrange(1,11)
        c = random.randrange(1,11)
        d = random.randrange(1,11)
        e = random.randrange(1,11)
        f = random.randrange(1,11)
        g = random.randrange(1,11)
        h = random.randrange(1,11)
        i = random.randrange(1,11)
        j = random.randrange(1,11)
        k = random.randrange(1,11)
        l = random.randrange(1,11)
        m = random.randrange(1,11)
        n = random.randrange(1,11)
        o = random.randrange(1,11)
        p = random.randrange(1,11)
        r = random.randrange(1,11)
        s = random.randrange(1,11)
        t = random.randrange(1,11)
        u = random.randrange(1,11)
        v = random.randrange(1,11)
        x = random.randrange(1,11)
        w = random.randrange(1,11)
        y = random.randrange(1,11)
        z = random.randrange(1,11)

        examp_tree =  ["r",["a",["c",a],["d",b],["e",["i",c],["j",d]]], ["b",["f",e],["g",f],["h",g]]]
        examp_tree_2= ["r",["a",["f",a],["g",b]],["b",["h",["o",["ae",c],["af",d]],["p",["ag",e],["ah",f]],["R",g]],["j",["s",h],["t",j]],["k",k],["c",["l",["v",l],["uu",m]],["m",n]],["d",["n",["w",o],["y",["aa",p],["ab",r]],["z",["ac",["ai",["am",s],["an",t]],["aj",["ao",u],["ap",w]],["ak",x],["al",y]],["ad",z]]]],["e",a]]]
        examp_tree_3 = ["r",['a',["c",a],["d",["h",b],["i",c]]],["b",["e",d],["f",["j",e],["k",f],["l",g]],["g",["m",h]]]]
        examp_tree_4 = ["a123,4.?5",a]
        examp_tree_5 = ["r",["a",["c",a],["d",b],["e",c],["f",d]],["b",["g",e],[" ",["h",f],["i",g]],["j",h]]]
        examp_tree_6 = ["", [" ", ["  ", a], ["   ", b], ["    ", ["     ", c], ["      ", d]]], ["       ", ["        ", e], ["         ", f], ["          ", g]]]
        examp_tree_7 = ['r',['a',['b',['c',z]]]]
        our_tree = examp_tree
        result = the4_original.chalchiuhtlicue(our_tree)
        our_tree = str(our_tree)
        result = str(result)
        file.write(our_tree)
        file.write(":::")
        file.write(result)
        file.write("\n")
t2 = time.time()
print(t2-t1)        


