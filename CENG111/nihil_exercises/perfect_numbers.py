#PERFECT NUMBERS
def divisor_adder(x):
    divisor_all = 0
    for i in range(1,int(x)/2 + 1):
        if int(x)%i == 0:
            divisor_all += i
    return divisor_all
def perfect_numbers(x):
    res = ([],[],[1])
    for i in range(2,x):
        if divisor_adder(i) == i:
            res[0].append(i)
        elif divisor_adder(i) > i:
            res[1].append(i)
        else:
            res[2].append(i)
    return res
