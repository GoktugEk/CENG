def palindromes(num):
    res= []
    for i in range(num+1):
        bin_i= str(bin(i))[2:]
        i = str(i)
        if (i[::-1] == i) and (bin_i[::-1] == bin_i):
            res.append(int(i))
    return res
