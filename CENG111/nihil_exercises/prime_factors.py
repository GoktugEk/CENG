def isprime(num):
    i = 2
    a = True
    while i**2 <= num:
        if num % i ==  0:
            a = False
        i+=1             
    return a

def find_factors(num):
    res = []
    for i in range(2,num):
        if num%i == 0:
            res.append(i)
    return res

def prime_factors(num):
    res = []
    if num == 2:
        return [2]
    for i in find_factors(num):
        if isprime(i):
            res.append(i)
    return res
